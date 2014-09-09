#include <QtCore>
#include <QXmlStreamReader>
#include <QXmlResultItems>
#include <QDomDocument>
#include <QXmlQuery>
#include <QVector>

#include "recordinfo.h"
#include "parser.h"

Parser::Parser()
{
}

QVector<RecordInfo*> Parser::parseXml(QByteArray& data)
{
    QString strQuery = R"*(//rss/channel/item/
            <record
                title="{title/text()}"
                description="{description/text}"
                date="{pubDate/text()}"
                url="{enclosure/@url}"
                length="{enclosure/@length}"
                type="{enclosure/@type}"
                guid="{guid/text()}"/>)*";

    QXmlQuery xQuery;
    xQuery.setFocus(data);
    xQuery.setQuery(strQuery);
    QXmlResultItems out;
    xQuery.evaluateTo(&out);

    QString url, title, date, guid, description, type, length;
    int tmp;
    QVector<RecordInfo*> records;
    QXmlItem item(out.next());
    while (!item.isNull())
    {
        if(item.isNode())
        {
            xQuery.setFocus(item);
            xQuery.setQuery("./@title/string()");
            xQuery.evaluateTo(&title);

            xQuery.setQuery("./@description/string()");
            xQuery.evaluateTo(&description);

            xQuery.setQuery("./@date/string()");
            xQuery.evaluateTo(&date);

            xQuery.setQuery("./@url/string()");
            xQuery.evaluateTo(&url);

            xQuery.setQuery("./@length/string()");
            xQuery.evaluateTo(&length);
            tmp = length.toInt(nullptr);

            xQuery.setQuery("./@type/string()");
            xQuery.evaluateTo(&type);

            xQuery.setQuery("./@guid/string()");
            xQuery.evaluateTo(&guid);

            //ignore records without mp3
            if(type.trimmed().compare("audio/mpeg", Qt::CaseInsensitive) != 0)
            {
                item = out.next();
                continue;
            }
            RecordInfo* rec = new RecordInfo();
            rec->setTitle(title.trimmed());
            rec->setUrl(url.trimmed());
            rec->setDate(date.trimmed());
            rec->setGuid(guid.trimmed());
            rec->setLength(tmp);
            rec->setDescription(description.trimmed());
            records.push_back(rec);
        }
        item = out.next();
    }
    return records;
}
