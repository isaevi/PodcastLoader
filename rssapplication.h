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
    //explicit RssApplication(QObject *parent = 0);
    explicit RssApplication(int &argc, char **argv);
    QNetworkAccessManager* networkAccessMenager() const {return _manager;}
    //QQmlEngine* qmlEngine() const {return _engine;}
signals:

public slots:

private:
    QNetworkAccessManager* _manager;
    //QQmlEngine* _engine;

};

#endif // RSSAPPLICATION_H
