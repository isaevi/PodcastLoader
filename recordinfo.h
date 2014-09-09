#ifndef RECORDINFO_H
#define RECORDINFO_H

#include <QObject>
#include <QString>
#include <QDateTime>

#include "feeddata.h"

class RecordInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(int length READ length WRITE setLength NOTIFY lengthChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(int downloadPercent READ downloadPercent WRITE setDownloadPercent NOTIFY downloadPercentChanged)

FeedData* _feed;
QString _title;
QUrl _url;
QString _guid;
QDateTime _date;
int _length;
QString _description;
int _downloadPercent;

public:
    RecordInfo();
    FeedData* getFeed () {return _feed;}
    void setFeed(FeedData* feed) {_feed = feed;}
    bool operator ==(const RecordInfo& other);
    QString title() const;
    QUrl url() const;
    QString guid() const;
    QDateTime date() const;
    int length() const;
    QString description() const;
    void setDate(QString date);
    int downloadPercent() const;

public slots:
    void setTitle(QString arg);
    void setUrl(QUrl arg);
    void setGuid(QString arg);
    void setDate(QDateTime arg);
    void setLength(int arg);
    void setDescription(QString arg);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void setDownloadPercent(int arg);

signals:
    void titleChanged(QString arg);
    void urlChanged(QUrl arg);
    void guidChanged(QString arg);
    void dateChanged(QDateTime arg);
    void lengthChanged(int arg);
    void descriptionChanged(QString arg);
    void downloadPercentChanged(int arg);
};

#endif // RECORDINFO_H
