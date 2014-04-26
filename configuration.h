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

    int feedCount() {return _feedCount;}
    FeedData* feedAt(const int index);
    void addFeed(QString feedUrl, QString feedDir, QString feedPrefix);
private:
    int _feedCount;
    QVector<FeedData*> _feeds;
};

#endif // CONFIGURATION_H
