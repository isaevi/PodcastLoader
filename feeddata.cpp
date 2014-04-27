#include <QMutexLocker>
#include "feeddata.h"

FeedData::FeedData(QString feedUrl, QString feedDir, QString feedPrefix)
{
    _feedUrl = feedUrl;
    _feedDir = feedDir;
    _feedPrefix = feedPrefix;
}

void FeedData::addProcessedGuid(const QString& guid)
{
    QMutexLocker lock(&_mutex);
    _processedGuids.insert(guid);
}

bool FeedData::isContainsAmongProcessed(const QString& guid)
{
    QMutexLocker lock(&_mutex);
    return _processedGuids.contains(guid);
}

QSet<QString> FeedData::getProcessedGuids()
{
    QMutexLocker lock(&_mutex);
    return _processedGuids;
}
