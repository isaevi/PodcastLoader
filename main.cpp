#include <QtQuick/QQuickView>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QDebug>

#include "rssapplication.h"
#include "entrypoint.h"

int main(int argc, char **argv)
{    
    QCoreApplication::addLibraryPath("plugins");
    EntryPoint entry;
    QNetworkAccessManager networkManager;
    RssApplication app(argc, argv, &networkManager);

    QQmlApplicationEngine engine;
    QQuickWindow::setDefaultAlphaBuffer(true);

    entry.setEngine(&engine);
    entry.registerObjectsInEngine();

    engine.load(QUrl("qrc:/main.qml"));
    //engine.load(QUrl("../PodcastLoader/main.qml"));

    return app.exec();
}
