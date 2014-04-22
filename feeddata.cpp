#include "feeddata.h"

FeedData::FeedData(QString feedUrl, QString feedDir, QString feedPrefix)
{
    _feedUrl = feedUrl;
    _feedDir = feedDir;
    _feedPrefix = feedPrefix;
}
