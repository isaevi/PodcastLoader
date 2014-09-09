#ifndef RSSFETCHER_H
#define RSSFETCHER_H

#include <QObject>
#include <QVector>
#include <QNetworkReply>

#include "recordinfo.h"
#include "feeddata.h"

class FeedData;
class QString;
class QUrls;

class RssFetcher : public QObject
{
    Q_OBJECT
public:
    RssFetcher(FeedData *feed);
    void Fetch(const QUrl& url);

public slots:
    void metaDataChanged();
    void error(QNetworkReply::NetworkError);
    void finished();

signals:
    void finished(QList<RecordInfo*> records, FeedData *feed);
    void canceled();

private:
    QNetworkReply *_currentReply;
    FeedData* _feed;
};

#endif // RSSFETCHER_H
