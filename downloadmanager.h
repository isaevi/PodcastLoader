#ifndef RECORDSMANAGER_H
#define RECORDSMANAGER_H

#include <QObject>
#include <QVector>

#include "recordinfo.h"
#include "downloader.h"
#include "feeddata.h"

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);
    ~DownloadManager();
signals:
    void recordFinished(RecordInfo* record);
    void downloadProgress(RecordInfo* rec, qint64 bytesReceived, qint64 bytesTotal);

public slots:
    Q_INVOKABLE
    void addRecordForDownloading(RecordInfo* record);

private:
    void hadMoreRecords();
    Downloader *findFirstFreeDownloader();
private slots:
    void downloaded(RecordInfo *rec);

private:
    QVector<RecordInfo*> _records;
    QVector<RecordInfo*> _queuedRecords;
    QVector<Downloader*> _loaders;
    Downloader _stub;
    const int PoolSize = 6;
    //QNetworkAccessManager : Currently, for the HTTP protocol on desktop platforms,
    //6 requests are executed in parallel for one host/port combination.
};

#endif // RECORDSMANAGER_H
