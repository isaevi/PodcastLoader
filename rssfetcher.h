#ifndef RSSFETCHER_H
#define RSSFETCHER_H

#include <QObject>
#include <QVector>
#include <QNetworkReply>
//#include <QNetworkAccessManager>

#include "recordinfo.h"
#include "feeddata.h"

class FeedData;
class QString;
//class QNetworkAccessManager;
//class QNetworkReply;
class QUrls;

class RssFetcher : public QObject
{
    Q_OBJECT
public:
    //RssFetcher(const FeedData feed, QNetworkAccessManager* networkManager);
    RssFetcher(const FeedData feed);
    void Fetch(const QUrl& url);

public slots:
    void readyRead();
    void metaDataChanged();
    void error(QNetworkReply::NetworkError);

signals:
    void finished(QVector<RecordInfo*> records);
    void canceled();

private:
    //QNetworkAccessManager _manager;
    QNetworkReply *_currentReply;
    FeedData _feed;
};

#endif // RSSFETCHER_H
