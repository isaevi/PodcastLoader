#ifndef FEEDDATA_H
#define FEEDDATA_H

#include <QUrl>
#include <QString>
#include <QSet>
#include <QMutex>

class FeedData
{
public:
    FeedData() {}
    FeedData(QString feedUrl, QString feedDir, QString feedPrefix);
    QUrl getFeedUrl() const {return _feedUrl;}
    QString getFeedDir() const {return _feedDir;}
    QString getFeedPrefix() const {return _feedPrefix;}
    void addProcessedGuid(const QString &guid);
    bool isContainsAmongProcessed(const QString& guid);
    QSet<QString> getProcessedGuids();
private:
    QUrl _feedUrl;
    QString _feedDir;
    QString _feedPrefix;
    QSet<QString> _processedGuids;
    QMutex _mutex;
};

#endif // FEEDDATA_H
