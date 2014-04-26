#include <QDomDocument>
#include <QFile>
#include <QDebug>

#include "configuration.h"
#include "feeddata.h"

const QString dirAttr = "dir";
const QString urlAttr = "url";
const QString prefixAttr = "prefix";
const QString feedNode = "Feed";
const QString guidNode = "Guid";

Configuration::Configuration() : _feedCount(0)
{
}

FeedData* Configuration::feedAt(const int index)
{
    Q_ASSERT(index < _feeds.size());
    return _feeds[index];
}

void Configuration::load()
{
    QFile file("config.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open configuration.";
        return;
    }

    QDomDocument document;
    if (!document.setContent(file.readAll()))
    {
        qDebug() << "Can't read configuration for loading.";
        return ;
    }

    QDomElement  element = document.documentElement().firstChildElement(feedNode);
    QString value;
    while ( !element.isNull() )
    {
        // do all you need to do with <name> element
        QString dir = element.attribute(dirAttr);
        QString url = element.attribute(urlAttr);
        QString prefix = element.attribute(prefixAttr);
        FeedData* feed = new FeedData(url, dir, prefix);

        QDomNode node = element.firstChild();
        while(!node.isNull())
        {
            value = node.nodeValue();
            feed->addProcessedGuid(value);
            node = node.nextSibling();
        }
        _feeds.append(feed);
        element = element.nextSiblingElement(feedNode);
    }
}

void Configuration::save()
{
    QFile file("config_new.xml");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Can't open configuration for writing.";
        return;
    }

    const int Indent = 4;

    QDomDocument doc;
    for(auto it = _feeds.begin(); it != _feeds.end(); ++it )
    {
        QDomElement node = doc.createElement(feedNode);
        node.setAttribute(urlAttr, (*it)->getFeedUrl().toString());
        node.setAttribute(dirAttr, (*it)->getFeedDir());
        node.setAttribute(prefixAttr, (*it)->getFeedPrefix());

        const QSet<QString> guids = (*it)->getProcessedGuids();
        for(auto guid : guids)
        {
            QDomElement list = doc.createElement(guidNode);
            list.setNodeValue(guid);
            node.appendChild(list);
        }
        doc.appendChild(node);
    }

//    QDomElement root = doc.createElement("doc");
//    QDomElement quote = doc.createElement("quote");
//    QDomElement translation = doc.createElement("translation");
//    QDomText quoteText = doc.createTextNode("Errare humanum est");
//    QDomText translationText = doc.createTextNode("To err is human");

//    doc.appendChild(root);
//    root.appendChild(quote);
//    root.appendChild(translation);
//    quote.appendChild(quoteText);
//    translation.appendChild(translationText);
    QDomProcessingInstruction pi = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ");
    doc.insertBefore(pi, QDomNode());

    QTextStream out(&file);
    doc.save(out, Indent);
}


void Configuration::addFeed(QString feedUrl, QString feedDir, QString feedPrefix)
{
    FeedData* feed = new FeedData(feedUrl, feedDir, feedPrefix);
    _feeds.append(feed);
}
