#ifndef FEEDDATA_H
#define FEEDDATA_H

#include <QUrl>
#include <QString>

class FeedData
{
QUrl _feedUrl;
QString _feedDir;
QString _feedPrefix;
public:
    FeedData() {}
    FeedData(QString feedUrl, QString feedDir, QString feedPrefix);
    QUrl getFeedUrl() const {return _feedUrl;}
    QString getFeedDir() const {return _feedDir;}
    QString getFeedPrefix() const {return _feedPrefix;}
};

#endif // FEEDDATA_H
