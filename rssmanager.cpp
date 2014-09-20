#include <QMutexLocker>
#include "rssmanager.h"
#include "rssfetcher.h"

RssManager::RssManager(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<RecordInfo> RssManager::rssRecords()
{
    return QQmlListProperty<RecordInfo>(this, 0, nullptr, RssManager::countRecords, RssManager::recordAt, nullptr);
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

void RssManager::gotInformationAboutFeedRecords(QList<RecordInfo *> rss, FeedData *feed)
{
    auto details = new FeedInformation();
    details->rssRecords = rss;
    for(auto rec : details->rssRecords)
        rec->setParent(this);
    details->state = Finished;
    bool needToSignal = false;
    {
        QMutexLocker lock(&_mutex);

        if(feedDetails.contains(feed))
            delete feedDetails[feed];
        feedDetails[feed] = details;

        if(_feedsToFetch.contains(feed))
        {
            std::copy(details->rssRecords.begin(), details->rssRecords.end(), std::back_inserter(_rssRecords));
            _feedsToFetch.removeOne(feed);
            needToSignal = _feedsToFetch.count() == 0;
        }
    }
    if(needToSignal)
    {
        emit rssRecordsChanged();
        emit endQueringRecords(feed);
    }
}

void RssManager::feedUrlWasChange(QUrl arg, FeedData* feed)
{
    Q_UNUSED(arg);
    //remove feed from cache
    QMutexLocker lock(&_mutex);
    FeedInformation* value = feedDetails.take(feed);
    if(value)
        delete value;
}

int RssManager::countRecords(QQmlListProperty<RecordInfo> *property)
{
    RssManager *manager = qobject_cast<RssManager *>(property->object);
    if (manager)
    {
        QMutexLocker lock(&(manager->_mutex));
        return manager->_rssRecords.count();
    }
    return 0;
}

RecordInfo *RssManager::recordAt(QQmlListProperty<RecordInfo> *property, int index)
{
    RssManager *manager = qobject_cast<RssManager *>(property->object);
    if (manager)
    {
        //The instance of RecordInfo could be modified only at UI where we have only one thread
        return manager->rssAt(index);
    }
    return nullptr;
}

void RssManager::resetQueue(QList<FeedData *> feeds)
{
    emit startQueringRecords();
    QMutexLocker lock(&_mutex);
    _rssRecords.clear();
    _feedsToFetch = feeds;
}

void RssManager::addFeedToQueue(FeedData *feed)
{
    bool needToSignal = false;
    {
        QMutexLocker lock(&_mutex);
        if(feedDetails.contains(feed))
        {
            const FeedInformation* details = feedDetails[feed];
            //ToDo: need to handle changes in settings during fetching
            if(details && details->state == Finished)
            {
                {
                    _rssRecords = details->rssRecords;
                    _feedsToFetch.removeOne(feed);
                    needToSignal = _feedsToFetch.count() == 0;
                }
            }
        }
        else
        {
            //add callback on changing feed's url for reseting cache
            connect(feed, SIGNAL(urlChanged(QUrl, FeedData*)), SLOT(feedUrlWasChange(QUrl, FeedData*)));

            auto info = new FeedInformation();
            info->state = Fetching;
            auto fetcher = new RssFetcher(feed);
            feedDetails.insert(feed, info);
            connect(fetcher, SIGNAL(finished(QList<RecordInfo*>, FeedData*)), SLOT(gotInformationAboutFeedRecords(QList<RecordInfo*>, FeedData*)));
            fetcher->Fetch(feed->url());
        }
    }
    if(needToSignal)
    {
        emit rssRecordsChanged();
        emit endQueringRecords(feed);
    }
}
