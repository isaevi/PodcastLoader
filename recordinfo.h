#ifndef RECORDINFO_H
#define RECORDINFO_H

#include <QString>
#include <QDateTime>

#include "feeddata.h"

class RecordInfo
{
QString _title;
QString _url;
QDateTime _date;
FeedData _feed;
public:
    RecordInfo();
    QString getTitle() const {return _title;}
    QString getUrl() const {return _url;}
    QDateTime getDate() const {return _date;}
    const FeedData& getFeed () const {return _feed;}
    void setTitle(const QString& title) {_title = title;}
    void setUrl(const QString& url) {_url = url;}
    void setDate(QString date);
    void setFeed(const FeedData& feed) {_feed = feed;}
    bool operator ==(const RecordInfo& other);
};

#endif // RECORDINFO_H
