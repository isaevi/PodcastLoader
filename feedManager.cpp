#include <QDomDocument>
#include <QFile>
#include <QDebug>

#include "feedmanager.h"
#include "feeddata.h"

const QString dirAttr = "dir";
const QString urlAttr = "url";
const QString prefixAttr = "prefix";
const QString titleAttr = "title";
const QString feedNode = "Feed";
const QString guidNode = "Guid";
const QString feedsConfiguration = "Configuration";
const QString configName = "config.xml";
const QString tempoparyConfigName = "config_new.xml";

FeedData* FeedManager::feedAt(const int index)
{
    Q_ASSERT(index >=0 && index < _feeds.size());
    return _feeds[index];
}

void FeedManager::load()
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
        QString title = element.attribute(titleAttr);
        QString dir = element.attribute(dirAttr);
        QString url = element.attribute(urlAttr);
        QString prefix = element.attribute(prefixAttr);
        FeedData* feed = new FeedData(title, url, dir, prefix, this);

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

void FeedManager::save()
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
        node.setAttribute(titleAttr, (*it)->title());
        node.setAttribute(urlAttr, (*it)->url().toString());
        node.setAttribute(dirAttr, (*it)->dir());
        node.setAttribute(prefixAttr, (*it)->prefix());

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


void FeedManager::addFeed(QString feedTitle, QString feedUrl, QString feedDir, QString feedPrefix)
{
    FeedData* feed = new FeedData(feedTitle, feedUrl, feedDir, feedPrefix, this);
    _feeds.append(feed);
    emit feedsChanged();
}

void FeedManager::addStubFeed()
{
    FeedData* feed = new FeedData();
    _feeds.append(feed);
    emit feedsChanged();
}

void FeedManager::resetFeedAt(const int index)
{
    FeedData* feed = feedAt(index);
    if(feed->empty())
    {
        _feeds.removeAt(index);
        //delete feed;
        feed->deleteLater();
    }
    emit feedsChanged();
}

void FeedManager::removeAt(const int index)
{
    FeedData* feed = feedAt(index);
    _feeds.removeAt(index);
    feed->deleteLater();
    emit feedsChanged();
}

QQmlListProperty<FeedData> FeedManager::feeds()
{
    return QQmlListProperty<FeedData>(this, 0, FeedManager::add, FeedManager::count, FeedManager::at, nullptr);
}

void FeedManager::add(QQmlListProperty<FeedData> *list, FeedData *feed)
{
    FeedManager *config = qobject_cast<FeedManager *>(list->object);
    if (config)
        config->addFeed("", feed->url().toString(), feed->dir(), feed->prefix());
}

int FeedManager::count(QQmlListProperty<FeedData> *list)
{
    FeedManager *config = qobject_cast<FeedManager *>(list->object);
    if (config)
        return config->feedCount();
    return 0;
}

FeedData* FeedManager::at(QQmlListProperty<FeedData> *list, int index)
{
    FeedManager *config = qobject_cast<FeedManager *>(list->object);
    if (config)
        return config->feedAt(index);
    return nullptr;
}

