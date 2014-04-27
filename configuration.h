#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QVector>

class FeedData;

class Configuration
{
public:
    Configuration();
    void load();
    void save();

    int feedCount() {return _feeds.size();}
    FeedData* feedAt(const int index);
    void addFeed(QString feedUrl, QString feedDir, QString feedPrefix);
private:
    QVector<FeedData*> _feeds;

    const QString dirAttr = "dir";
    const QString urlAttr = "url";
    const QString prefixAttr = "prefix";
    const QString feedNode = "Feed";
    const QString guidNode = "Guid";
    const QString feedsConfiguration = "Configuration";
    const QString configName = "config.xml";
    const QString tempoparyConfigName = "config_new.xml";

};

#endif // CONFIGURATION_H
