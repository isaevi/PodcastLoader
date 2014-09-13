#include <QtCore>

#include "recordinfo.h"

RecordInfo::RecordInfo(QObject *parent) : QObject(parent), _downloadPercent(0)
{

}

bool RecordInfo::operator ==(const RecordInfo& other)
{
    return _title.compare(other._title) == 0 && _url.matches(other._url, QUrl::None) && _date == other._date;
}

QString RecordInfo::title() const
{
    return _title;
}

QUrl RecordInfo::url() const
{
    return _url;
}

QString RecordInfo::guid() const
{
    return _guid;
}

QDateTime RecordInfo::date() const
{
    return _date;
}

void RecordInfo::setTitle(QString arg)
{
    if (_title == arg)
        return;

    _title = arg;
    emit titleChanged(arg);
}

void RecordInfo::setUrl(QUrl arg)
{
    if (_url == arg)
        return;

    _url = arg;
    emit urlChanged(arg);
}

void RecordInfo::setGuid(QString arg)
{
    if (_guid == arg)
        return;

    _guid = arg;
    emit guidChanged(arg);
}

void RecordInfo::setDate(QString date)
{
    //    QString date = "Sat, 19 Apr 2014 22:30:00 +0000";
        const QString format = "ddd, dd MMM yyyy hh:mm:ss";
    //    QLocale loc( QLocale::C );
    //    QDateTime result = loc.toDateTime(date, format);
        _date = QDateTime::fromString(date.remove(QRegExp("(\\s[+]\\d\\d\\d\\d)")), format);
        if(!_date.isValid())
            qWarning() << date;
}

int RecordInfo::downloadPercent() const
{
    return _downloadPercent;
}

int RecordInfo::length() const
{
    return _length;
}

QString RecordInfo::description() const
{
    return _description;
}

void RecordInfo::setDate(QDateTime arg)
{
    if (_date == arg)
        return;

    _date = arg;
    emit dateChanged(arg);
}

void RecordInfo::setLength(int arg)
{
    if (_length == arg)
        return;

    _length = arg;
    emit lengthChanged(arg);
}

void RecordInfo::setDescription(QString arg)
{
    if (_description == arg)
        return;

    _description = arg;
    emit descriptionChanged(arg);
}

void RecordInfo::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    setDownloadPercent(bytesReceived * 100/bytesTotal);
}

void RecordInfo::setDownloadPercent(int arg)
{
    if (_downloadPercent == arg)
        return;

    _downloadPercent = arg;
    emit downloadPercentChanged(arg);
}

