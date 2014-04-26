#include "feeddata.h"

FeedData::FeedData(QString feedUrl, QString feedDir, QString feedPrefix)
{
    _feedUrl = feedUrl;
    _feedDir = feedDir;
    _feedPrefix = feedPrefix;
}

void FeedData::addProcessedGuid(const QString& guid)
{
    _processedGuids.insert(guid);
}

bool FeedData::isContainsAmongProcessed(const QString& guid)
{
    return _processedGuids.contains(guid);
}
