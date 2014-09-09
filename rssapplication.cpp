#include <QNetworkAccessManager>
#include <QQmlEngine>

#include "rssapplication.h"

RssApplication::RssApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
    _manager = new QNetworkAccessManager(this);
//    _engine = new QQmlEngine(this);
}
