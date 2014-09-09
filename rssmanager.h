#ifndef RSSMANAGER_H
#define RSSMANAGER_H

#include <QObject>
#include <QQmlListProperty>
#include <QMap>
#include <QMutex>

#include "recordinfo.h"

class FeedData;
class RssFetcher;

enum FetchState
{
    Fetching = 0,
    Finished = 1
};

struct FeedInormation
{
    QList<RecordInfo*> rssRecords;
    QAtomicInt state;
    RssFetcher* fetcher;
};

typedef QMap<FeedData*, FeedInormation> FeedsDetails;

class RssManager : public QObject
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
    void rssRecordsChanged(QQmlListProperty<RecordInfo> arg);
    //void rssRecordsChanged();

private slots:
    void finishedEx(QList<RecordInfo *> rss, FeedData *feed);
private:
    static void appendRecord(QQmlListProperty<RecordInfo> *property, RecordInfo *value);
    static int countRecords(QQmlListProperty<RecordInfo> *property);
    static RecordInfo* recordAt(QQmlListProperty<RecordInfo> *property, int index);

    QList<RecordInfo*> _rssRecords;
    FeedsDetails feedDetails;
    mutable QMutex _mutex;
};

#endif // RSSMANAGER_H
