#ifndef RSSMANAGER_H
#define RSSMANAGER_H

#include <QObject>
#include <QQmlListProperty>
#include <QMap>
#include <QMutex>

#include "recordinfo.h"
#include "helperinterfaces.h"

class FeedData;
class RssFetcher;

enum FetchState
{
    Fetching = 0,
    Finished = 1
};

struct FeedInformation
{
    QList<RecordInfo*> rssRecords;
    QAtomicInt state;
    RssFetcher* fetcher;
};

typedef QMap<FeedData*, FeedInformation*> FeedsDetails;

class RssManager : public QObject, public IFeedInformationFetcher
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<RecordInfo> rssRecords READ rssRecords NOTIFY rssRecordsChanged)
public:
    explicit RssManager(QObject *parent = 0);

    QQmlListProperty<RecordInfo> rssRecords();
    Q_INVOKABLE
    void setActiveFeed(FeedData* feed);
    Q_INVOKABLE
    RecordInfo* rssAt(int index);
signals:
    //void rssRecordsChanged(QQmlListProperty<RecordInfo> arg);
    void rssRecordsChanged();
    void startQueringRecords();
    void endQueringRecords(FeedData *forFeed);
    //void rssRecordsChanged();

private slots:
    void finishedEx(QList<RecordInfo *> rss, FeedData *feed);
private:
    static void appendRecord(QQmlListProperty<RecordInfo> *property, RecordInfo *value);
    static int countRecords(QQmlListProperty<RecordInfo> *property);
    static RecordInfo* recordAt(QQmlListProperty<RecordInfo> *property, int index);

    QList<RecordInfo*> _rssRecords;
    QList<FeedData*> _feedsToFetch;
    FeedsDetails feedDetails;
    mutable QMutex _mutex;

    // IFeedInformationFetcher interface
private:
    void resetQueue(QList<FeedData*> feeds);
    void addFeedToQueue(FeedData *feed);
};

#endif // RSSMANAGER_H
