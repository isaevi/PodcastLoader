#include <QMutexLocker>
#include "feeddata.h"

FeedData::FeedData(QString feedTitle, QString  feedUrl, QString feedDir, QString feedPrefix) : QObject()
{
    _title = feedTitle;
    _url = feedUrl;
    _dir = feedDir;
    _prefix = feedPrefix;
    _empty = false;
    if(_title.isEmpty())
        _title = "Please, enter the title";

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

QUrl FeedData::url() const
{
    return _url;
}

QString FeedData::dir() const
{
    return _dir;
}

QString FeedData::prefix() const
{
    return _prefix;
}

QString FeedData::title() const
{
    return _title;
}

bool FeedData::empty() const
{
    return _empty;
}

void FeedData::setUrl(QUrl arg)
{
    if (_url != arg) {
        _url = arg;
        emit urlChanged(arg);
    }
}

void FeedData::setDir(QString arg)
{
    if (_dir != arg) {
        _dir = arg;
        emit dirChanged(arg);
    }
}

void FeedData::setPrefix(QString arg)
{
    if (_prefix != arg) {
        _prefix = arg;
        emit prefixChanged(arg);
    }
}

void FeedData::setTitle(QString arg)
{
    if (_title != arg) {
        _title = arg;
        emit titleChanged(arg);
    }
}

void FeedData::setEmpty(bool arg)
{
    if (_empty == arg)
        return;

    _empty = arg;
    emit emptyChanged(arg);
}

