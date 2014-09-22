#ifndef RSSAPPLICATION_H
#define RSSAPPLICATION_H

#include <QGuiApplication>

class QNetworkAccessManager;
class QQmlEngine;

class RssApplication;
#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<RssApplication*>(QGuiApplication::instance()))

class RssApplication : public QGuiApplication
{
    Q_OBJECT
public:
    explicit RssApplication(int &argc, char **argv, QNetworkAccessManager* networkManager);
    QNetworkAccessManager* networkAccessMenager() const {return _manager;}
signals:

public slots:

private:
    QNetworkAccessManager* _manager;
    //QQmlEngine* _engine;

};

#endif // RSSAPPLICATION_H
