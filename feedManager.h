#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QVector>
#include <QQmlListProperty>
#include "feeddata.h"

//class FeedData;

class FeedManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<FeedData> feeds READ feeds NOTIFY feedsChanged)
public:
    void load();
    void save();
    int feedCount() {return _feeds.size();}
    FeedManager(QObject* parent = nullptr);

    QQmlListProperty<FeedData> feeds();
    Q_INVOKABLE
    FeedData* feedAt(const int index);
    Q_INVOKABLE
    FeedData* addFeed(QString feedTitle, QString feedUrl, QString feedDir, QString feedPrefix);
    Q_INVOKABLE
    void addStubFeed();
    Q_INVOKABLE
    void resetFeedAt(const int index);
    Q_INVOKABLE
    void removeAt(const int index);
signals:
    void feedsChanged();
private:
    static void add(QQmlListProperty<FeedData> *list, FeedData *feed);
    static int count(QQmlListProperty<FeedData> *list);
    static FeedData* at(QQmlListProperty<FeedData> *list, int index);
    QList<FeedData*> _feeds;
    FeedDataAggregate* _allFeedsStub;
};

#endif // CONFIGURATION_H
