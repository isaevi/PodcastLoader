#include <QByteArray>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include "downloader.h"
#include "rssapplication.h"

Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
    _isBusy = false;
    _reply = nullptr;
}

Downloader::~Downloader()
{

}

bool Downloader::get(RecordInfo* rec)
{
    if(isBusy())
        return false;
    _rec = rec;
    _isBusy = true;
    QNetworkRequest request(rec->getUrl());
    if(_reply)
    {
        disconnect(_reply, 0, this, 0);
        _reply->deleteLater();
    }
    _reply = qApp->networkAccessMenager()->get(request);
    connect(_reply, SIGNAL(finished()), SLOT(finished()));
    connect(_reply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(downloadProgress(qint64,qint64)));

    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(error(QNetworkReply::NetworkError)));
    return true;
}

void Downloader::PrepareDirectory(QString title)
{
    QFileInfo info(title);
    QDir dir;
    dir.mkpath(info.absolutePath());
}

void Downloader::finished()
{
    QByteArray downloadedData = _reply->readAll();
    QString title = _rec->getTitle().replace(QRegExp("[/:*?\"<>| ,]"), "_");
    title = _rec->getFeed()->getFeedDir() + "\\" + _rec->getFeed()->getFeedPrefix() + "_" + _rec->getDate().toString("yyMMdd") + "_" + title + ".mp3";
    PrepareDirectory(title);
    QFile file(title);
    if(!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Couldn't create file:\n\t\t" << title;
        _isBusy = false;
        emit errorHappen();
        return;
    }
    file.write(downloadedData);
    file.close();

    _isBusy = false;
    _reply->deleteLater();
    _reply = nullptr;
    _rec->getFeed()->addProcessedGuid(_rec->getGuid());
    emit downloaded(_rec);
}


void Downloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    emit downloadProgress(_rec, bytesReceived, bytesTotal);
}

void Downloader::error(QNetworkReply::NetworkError error)
{
    qDebug() << "Error #" << error << "\t" << _rec->getTitle();
    _reply->deleteLater();
    _reply = nullptr;
}
