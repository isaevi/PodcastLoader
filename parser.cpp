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
                date="{pubDate/text()}"
                url="{enclosure/@url}"
                guid="{guid/text()}"/>)*";

    QXmlQuery xQuery;
    xQuery.setFocus(data);
    xQuery.setQuery(strQuery);
    QXmlResultItems out;
    xQuery.evaluateTo(&out);

    QString link, title, date, guid;
    QVector<RecordInfo*> records;
    QXmlItem item(out.next());
    while (!item.isNull())
    {
        if(item.isNode())
        {
            xQuery.setFocus(item);
            xQuery.setQuery("./@title/string()");
            xQuery.evaluateTo(&title);

            xQuery.setQuery("./@date/string()");
            xQuery.evaluateTo(&date);

            xQuery.setQuery("./@url/string()");
            xQuery.evaluateTo(&link);

            xQuery.setQuery("./@guid/string()");
            xQuery.evaluateTo(&guid);

            RecordInfo* rec = new RecordInfo();
            rec->setTitle(title.trimmed());
            rec->setUrl(link.trimmed());
            rec->setDate(date.trimmed());
            records.push_back(rec);
        }
        item = out.next();
    }
    return records;
}
