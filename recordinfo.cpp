#include <QtCore>

#include "recordinfo.h"

RecordInfo::RecordInfo()
{
}

void RecordInfo::setDate(const QString &date)
{
//    QString date = "Sat, 19 Apr 2014 22:30:00 +0000";
    const QString format = "ddd, dd MMM yyyy hh:mm:ss '+0000'";
//    QLocale loc( QLocale::C );
//    QDateTime result = loc.toDateTime(date, format);
    QDateTime result = QDateTime::fromString(date, format);
    _date = QDateTime::fromString(date, format);
    if(!_date.isValid())
        qWarning() << date;
}


bool RecordInfo::operator ==(const RecordInfo& other)
{
    return _title.compare(other._title) == 0 && _url.compare(other._url) && _date == other._date;
}
