#include <QtWidgets>
#include <QtQuick/QQuickView>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QDebug>

#include "rssapplication.h"
#include "rsslist.h"
#include "entrypoint.h"

int main(int argc, char **argv)
{    
    RssApplication app(argc, argv);

    QQmlEngine engine;
    QQmlComponent component(&engine);
    QQuickWindow::setDefaultAlphaBuffer(true);

    EntryPoint entry;
    entry.setEngine(&engine);
    entry.registerObjectsInEngine();

    //component.loadUrl(QUrl("qrc:/main.qml"));
    component.loadUrl(QUrl("../PodcastLoader/main.qml"));
    if ( component.isReady() )
        component.create();
    else
        qWarning() << component.errorString();

    return app.exec();
//    RssApplication app(argc, argv);
//    //QQmlApplicationEngine engine("addFeedDialog.qml");
//    RSSListing *rsslisting = new RSSListing;
//    rsslisting->show();
//    return app.exec();
}
