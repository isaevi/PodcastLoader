#include <QNetworkAccessManager>
#include <QQmlEngine>

#include "rssapplication.h"

RssApplication::RssApplication(int &argc, char **argv, QNetworkAccessManager *networkManager) :
    QGuiApplication(argc, argv)
{
    _manager = networkManager;
}
