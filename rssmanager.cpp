#include <QMutexLocker>
#include "rssmanager.h"
#include "rssfetcher.h"

RssManager::RssManager(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<RecordInfo> RssManager::rssRecords()
{
    return QQmlListProperty<RecordInfo>(this, 0, /*appendRecord*/nullptr, RssManager::countRecords, RssManager::recordAt, nullptr);
}

void RssManager::setActiveFeed(FeedData *feed)
{
    feed->queueFeedToFetch(this);
}

RecordInfo *RssManager::rssAt(int index)
{
    QMutexLocker lock(&_mutex);
    Q_ASSERT(index >= 0 && index < _rssRecords.size());
    return _rssRecords[index];
}

void RssManager::finishedEx(QList<RecordInfo *> rss, FeedData *feed)
{
    //QMutexLocker lock(&_mutex);
    FeedInformation* details = feedDetails[feed];
    Q_ASSERT(details);
    //return QQmlListProperty<FeedData>(this, 0, FeedManager::add, FeedManager::count, FeedManager::at, nullptr);
    details->rssRecords = rss;
    for(auto rec : details->rssRecords)
        rec->setParent(this);
    details->state.store(Finished);
    bool needToSignal = false;
    {
//        qWarning("finishedEx second in");
        QMutexLocker lock(&_mutex);
//        qWarning("finishedEx second pass");
        //_rssRecords = details->rssRecords;
        std::copy(details->rssRecords.begin(), details->rssRecords.end(), std::back_inserter(_rssRecords));

        feedDetails[feed] = details;

        _feedsToFetch.removeOne(feed);
        needToSignal = _feedsToFetch.count() == 0;
    }
    //rssRecordsChanged(details.rssRecords);
    //emit rssRecordsChanged(RssManager::rssRecords());
    if(needToSignal)
    {
        emit rssRecordsChanged();
        emit endQueringRecords(feed);
    }
//    qWarning("finishedEx second out");
}

void RssManager::appendRecord(QQmlListProperty<RecordInfo> *property, RecordInfo *value)
{
    //nope
}

int RssManager::countRecords(QQmlListProperty<RecordInfo> *property)
{
    RssManager *manager = qobject_cast<RssManager *>(property->object);
    if (manager)
    {
//        qWarning("countRecords in");
        QMutexLocker lock(&(manager->_mutex));
//        qWarning("countRecords pass");
        return manager->_rssRecords.count();
    }
    return 0;
}

RecordInfo *RssManager::recordAt(QQmlListProperty<RecordInfo> *property, int index)
{
    RssManager *manager = qobject_cast<RssManager *>(property->object);
    if (manager)
    {
        return manager->rssAt(index);
    }
    return nullptr;
}

void RssManager::resetQueue(QList<FeedData *> feeds)
{
    emit startQueringRecords();
    QMutexLocker lock(&_mutex);
    _rssRecords.clear();
    //_feedsToFetch.clear();
    _feedsToFetch = feeds;
}

void RssManager::addFeedToQueue(FeedData *feed)
{
    bool needToSignal = false;
    {
        QMutexLocker lock(&_mutex);
        //ToDo: inspect posibilities to use feedDetails from different threats
        if(feedDetails.contains(feed))
        {
            const FeedInformation* details = feedDetails[feed];
            //ToDo: need to handle changes in settings during fetching
            if(details && details->state.load() == Finished)
            {
                //rssRecords = details.rssRecords;
                {
                    //QMutexLocker lock(&_mutex);
                    //_rssRecords = rssRecords;
                    _rssRecords = details->rssRecords;
                    _feedsToFetch.removeOne(feed);
                    needToSignal = _feedsToFetch.count() == 0;
                }
            }
        }
        else
        {
            FeedInformation* info = new FeedInformation();
            info->state.store(Fetching);
            info->fetcher = new RssFetcher(feed);
            feedDetails.insert(feed, info);
            connect(info->fetcher, SIGNAL(finished(QList<RecordInfo*>, FeedData*)), this, SLOT(finishedEx(QList<RecordInfo*>, FeedData*)));
            info->fetcher->Fetch(feed->url());
        }
//        qWarning("setActiveFeed out");
    }
    if(needToSignal)
    {
//        qWarning("setActiveFeed call to signal");
        //rssRecordsChanged(rssRecords);
        //emit rssRecordsChanged(RssManager::rssRecords());
        emit rssRecordsChanged();
        emit endQueringRecords(feed);
    }
}
