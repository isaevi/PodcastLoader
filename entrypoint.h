#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <QObject>
#include "configuration.h"

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
};

#endif // ENTRYPOINT_H
