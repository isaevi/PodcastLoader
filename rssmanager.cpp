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
    emit startQueringRecords();
    bool needToSignal = false;
    //QList<RecordInfo*> rssRecords;
    {
//        qWarning("setActiveFeed in");
        QMutexLocker lock(&_mutex);
//        qWarning("setActiveFeed pass");

        //ToDo: inspect posibilities to use feedDetails from different threats
        if(feedDetails.contains(feed))
        {
            const FeedInormation& details = feedDetails[feed];
            //ToDo: need to handle changes in settings during fetching
            if(details.state.load() == Finished)
            {
                //rssRecords = details.rssRecords;
                {
                    //QMutexLocker lock(&_mutex);
                    //_rssRecords = rssRecords;
                    _rssRecords = details.rssRecords;
                    needToSignal = true;
                }
            }
        }
        else
        {
            FeedInormation info;
            info.state.store(Fetching);
            info.fetcher = new RssFetcher(feed);
            feedDetails.insert(feed, info);
            connect(info.fetcher, SIGNAL(finished(QList<RecordInfo*>, FeedData*)), this, SLOT(finishedEx(QList<RecordInfo*>, FeedData*)));
            info.fetcher->Fetch(feed->url());
        }
//        qWarning("setActiveFeed out");
    }
    if(needToSignal)
    {
//        qWarning("setActiveFeed call to signal");
        //rssRecordsChanged(rssRecords);
        emit rssRecordsChanged(RssManager::rssRecords());
        emit endQueringRecords(feed);
    }
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
    FeedInormation details = feedDetails[feed];
    //return QQmlListProperty<FeedData>(this, 0, FeedManager::add, FeedManager::count, FeedManager::at, nullptr);
    details.rssRecords = rss;
    for(auto rec : details.rssRecords)
        rec->setParent(this);
    details.state.store(Finished);
    {
//        qWarning("finishedEx second in");
        QMutexLocker lock(&_mutex);
//        qWarning("finishedEx second pass");
        _rssRecords = details.rssRecords;
        feedDetails[feed] = details;
    }
    //rssRecordsChanged(details.rssRecords);
    emit rssRecordsChanged(RssManager::rssRecords());
    emit endQueringRecords(feed);
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
