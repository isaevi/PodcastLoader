#include <QDomDocument>
#include <QFile>
#include <QDebug>

#include "configuration.h"
#include "feeddata.h"

Configuration::Configuration()
{
}

FeedData* Configuration::feedAt(const int index)
{
    Q_ASSERT(index < _feeds.size());
    return _feeds[index];
}

void Configuration::load()
{
    QFile file(configName);
    if(!file.open(QFile::ReadOnly | QFile::Text) || !file.exists())
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
            if(node.hasChildNodes())
            {
                value = node.firstChild().nodeValue();
                if(!value.isEmpty())
                    feed->addProcessedGuid(value);
            }
            node = node.nextSibling();
        }
        _feeds.append(feed);
        element = element.nextSiblingElement(feedNode);
    }
    file.close();
}

void Configuration::save()
{
    QFile file(tempoparyConfigName);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Couldn't open configuration for writing.";
        return;
    }

    const int Indent = 4;

    QDomDocument doc;
    QDomElement root = doc.createElement(feedsConfiguration);
    doc.appendChild(root);
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
            QDomText text = doc.createTextNode(guid);
            list.appendChild(text);
            node.appendChild(list);
        }
        root.appendChild(node);
    }

    QDomProcessingInstruction pi = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ");
    doc.insertBefore(pi, QDomNode());

    QTextStream out(&file);
    doc.save(out, Indent);
    QFile oldConfig(configName);
    if(!oldConfig.remove())
    {
        qDebug() << "Couldn't remove old configuration.";
        return;
    }
    if(!file.rename(configName))
        qDebug() << "Couldn't rename configuration.";
}


void Configuration::addFeed(QString feedUrl, QString feedDir, QString feedPrefix)
{
    FeedData* feed = new FeedData(feedUrl, feedDir, feedPrefix);
    _feeds.append(feed);
}
