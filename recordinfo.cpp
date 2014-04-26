#include <QtCore>

#include "recordinfo.h"

RecordInfo::RecordInfo()
{
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


bool RecordInfo::operator ==(const RecordInfo& other)
{
    return _title.compare(other._title) == 0 && _url.compare(other._url) && _date == other._date;
}
