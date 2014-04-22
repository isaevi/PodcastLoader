#include <QString>
#include <QNetworkReply>
#include <QUrl>
#include <QXmlStreamReader>

#include "rssfetcher.h"
#include "parser.h"
#include "feeddata.h"
#include "rssapplication.h"

RssFetcher::RssFetcher(const FeedData feed) : QObject()
{
    _feed = feed;
    _currentReply = nullptr;
}

void RssFetcher::Fetch(const QUrl &url)
{
    QNetworkRequest request(url);
    if (_currentReply) {
        _currentReply->disconnect(this);
        _currentReply->deleteLater();
    }
    _currentReply = qApp->networkAccessMenager()->get(request);
    connect(_currentReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(_currentReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect(_currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void RssFetcher::metaDataChanged()
{
    QUrl redirectionTarget = _currentReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (redirectionTarget.isValid()) {
        Fetch(redirectionTarget);
    }
}

void RssFetcher::readyRead()
{
    int statusCode = _currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode >= 200 && statusCode < 300) {
        QByteArray data = _currentReply->readAll();
        QVector<RecordInfo*> records = Parser::parseXml(data);
        for(auto rec : records)
            rec->setFeed(_feed);
        emit finished(records);
    }
}

void RssFetcher::error(QNetworkReply::NetworkError)
{
    qWarning("error retrieving RSS feed");
    _currentReply->disconnect(this);
    _currentReply->deleteLater();
    _currentReply = nullptr;
    emit canceled();
}

