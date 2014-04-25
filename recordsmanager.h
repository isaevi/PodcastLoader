#ifndef RECORDSMANAGER_H
#define RECORDSMANAGER_H

#include <QObject>
#include <QVector>

#include "recordinfo.h"
#include "downloader.h"
#include "feeddata.h"

class RecordsManager : public QObject
{
    Q_OBJECT
public:
    explicit RecordsManager(QObject *parent = 0);
    ~RecordsManager();
signals:
    void recordFinished(RecordInfo* record);
    void downloadProgress(RecordInfo* rec, qint64 bytesReceived, qint64 bytesTotal);

public slots:
    void finishedEx(QVector<RecordInfo*> records);

private:
    void hadMoreRecords();
    Downloader *findFirstFreeDownloader();
private slots:
    void downloaded(RecordInfo *rec);

private:
    QVector<RecordInfo*> _records;
    QVector<RecordInfo*> _finishedRecords;
    QVector<RecordInfo*> _queuedRecords;
    QVector<Downloader*> _loaders;
    Downloader _stub;
    const int PoolSize = 10;
};

#endif // RECORDSMANAGER_H
