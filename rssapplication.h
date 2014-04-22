#ifndef RSSAPPLICATION_H
#define RSSAPPLICATION_H

#include <QApplication>

class QNetworkAccessManager;

class RssApplication;
#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<RssApplication*>(QApplication::instance()))

class RssApplication : public QApplication
{
    Q_OBJECT
public:
    //explicit RssApplication(QObject *parent = 0);
    explicit RssApplication(int &argc, char **argv);
    QNetworkAccessManager* networkAccessMenager() const {return _manager;}
signals:

public slots:

private:
    QNetworkAccessManager* _manager;

};

#endif // RSSAPPLICATION_H
