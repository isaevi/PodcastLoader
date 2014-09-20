#ifndef FEEDDATA_H
#define FEEDDATA_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QSet>
#include <QMutex>

class IFeedInformationFetcher;

class FeedData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix NOTIFY prefixChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool empty READ empty WRITE setEmpty NOTIFY emptyChanged)
    Q_PROPERTY(bool isAggregateStub READ isAggregateStub WRITE setIsAggregateStub NOTIFY isAggregateStubChanged)
public:
    FeedData(QObject* parent = nullptr);
    FeedData(QString feedTitle, QString feedUrl, QString feedDir, QString feedPrefix, QObject *parent);

    void addProcessedGuid(const QString &guid);
    bool isContainsAmongProcessed(const QString& guid);
    QSet<QString> getProcessedGuids();
    QUrl url() const;
    QString dir() const;
    QString prefix() const;
    QString title() const;    
    bool empty() const;
    bool isAggregateStub() const;
    virtual void queueFeedToFetch(IFeedInformationFetcher* fetcher);

public slots:
    void setUrl(QUrl arg);
    void setDir(QString arg);
    void setPrefix(QString arg);
    void setTitle(QString arg);
    void setEmpty(bool arg);
    void setIsAggregateStub(bool arg);

signals:
    void urlChanged(QUrl arg, FeedData* feed);
    void dirChanged(QString arg);
    void prefixChanged(QString arg);
    void titleChanged(QString arg);
    void emptyChanged(bool arg);
    void isAggregateStubChanged(bool arg);

private:
    QSet<QString> _processedGuids;
    QMutex _mutex;
    QUrl _url;
    QString _dir;
    QString _prefix;
    QString _title;
    bool _empty;
    bool _isAggregateStub;
};

class FeedDataAggregate : public FeedData {
    Q_OBJECT
public:
    FeedDataAggregate(QObject* parent = nullptr);
    FeedDataAggregate(QString feedTitle, QString feedUrl, QString feedDir, QString feedPrefix, QObject *parent);

    // FeedData interface
public:
    void queueFeedToFetch(IFeedInformationFetcher *fetcher);
public slots:
    void addFeed(FeedData* feed);
    void removeFeed(FeedData* feed);
private:
    QList<FeedData*> _agregatedFeeds;
};

#endif // FEEDDATA_H
