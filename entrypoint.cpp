#include <QQmlEngine>
#include <QQmlContext>
#include <QtQml/QQmlComponent>
#include "entrypoint.h"
#include "feeddata.h"

EntryPoint::EntryPoint() : QObject(), _engine(nullptr)
{
}

EntryPoint::~EntryPoint()
{
    config.save();
}

void EntryPoint::setEngine(QQmlEngine* engine)
{
    _engine = engine;
}

void EntryPoint::registerObjectsInEngine()
{
    qmlRegisterType<FeedData>("com.podcaster.data", 1, 0, "FeedData");
    qmlRegisterType<RecordInfo>("com.podcaster.data", 1, 0, "RecordInfo");
    config.load();
    if(_engine != nullptr)
    {
        _engine->rootContext()->setContextProperty("config", &config);
        _engine->rootContext()->setContextProperty("rssManager", &rssManager);
        _engine->rootContext()->setContextProperty("downloader", &recordsManager);
    }
}
