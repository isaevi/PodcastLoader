#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml/QQmlComponent>
#include "entrypoint.h"
#include "feeddata.h"

EntryPoint::EntryPoint() : QObject(), _engine(nullptr)
{
}

EntryPoint::~EntryPoint()
{
    feedManager.save();
}

void EntryPoint::setEngine(QQmlApplicationEngine* engine)
{
    _engine = engine;
}

void EntryPoint::registerObjectsInEngine()
{
    qmlRegisterType<FeedData>("com.podcaster.data", 1, 0, "FeedData");
    qmlRegisterType<RecordInfo>("com.podcaster.data", 1, 0, "RecordInfo");
    feedManager.load();
    if(_engine != nullptr)
    {
        _engine->rootContext()->setContextProperty("feedManager", &feedManager);
        _engine->rootContext()->setContextProperty("rssManager", &rssManager);
        _engine->rootContext()->setContextProperty("downloader", &downloadManager);
    }
}
