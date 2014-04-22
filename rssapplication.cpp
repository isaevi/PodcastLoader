#include <QNetworkAccessManager>

#include "rssapplication.h"

RssApplication::RssApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
    _manager = new QNetworkAccessManager(this);
}
