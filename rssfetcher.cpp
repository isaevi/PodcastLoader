#include <QString>
#include <QNetworkReply>
#include <QUrl>
#include <QXmlStreamReader>

#include "rssfetcher.h"
#include "parser.h"
#include "feeddata.h"
#include "rssapplication.h"

RssFetcher::RssFetcher(FeedData *feed) : QObject()
{
    _feed = feed;
    _currentReply = nullptr;
}

void RssFetcher::Fetch(const QUrl &url)
{
    QNetworkRequest request(url);
    if (_currentReply) {
        _currentReply->disconnect(this);
        _currentReply->abort();
        _currentReply->deleteLater();
    }
    _currentReply = qApp->networkAccessMenager()->get(request);
    connect(_currentReply, SIGNAL(finished()), SLOT(finished()));
    connect(_currentReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect(_currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void RssFetcher::metaDataChanged()
{
    QUrl redirectionTarget = _currentReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (redirectionTarget.isValid()) {
        Fetch(_currentReply->url().resolved(redirectionTarget));
    }
}

void RssFetcher::finished()
{
    int statusCode = _currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode >= 200 && statusCode < 300) {
        QByteArray data = _currentReply->readAll();
        QVector<RecordInfo*> records = Parser::parseXml(data);
        QList<RecordInfo*> result;
        for(auto rec : records)
        {
            if(!_feed->isContainsAmongProcessed(rec->guid()))
            {
                rec->setFeed(_feed);
                result.append(rec);
            }
        }
        emit finished(result, _feed);
    }
    else
        emit canceled();
    _currentReply->deleteLater();
    _currentReply = nullptr;
}

void RssFetcher::error(QNetworkReply::NetworkError)
{
    qWarning("error retrieving RSS feed");
    _currentReply->disconnect(this);
    _currentReply->deleteLater();
    _currentReply = nullptr;
    emit canceled();
}

