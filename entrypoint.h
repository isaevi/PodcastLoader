#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <QObject>
#include "feedmanager.h"
#include "rssmanager.h"
#include "recordsmanager.h"

class QQmlEngine;

class EntryPoint : public QObject
{
    Q_OBJECT
public:
    EntryPoint();
    ~EntryPoint();
    void setEngine(QQmlEngine* engine);
    void registerObjectsInEngine();
private:
    QQmlEngine* _engine;
    FeedManager config;
    RssManager rssManager;
    RecordsManager recordsManager;
};

#endif // ENTRYPOINT_H
