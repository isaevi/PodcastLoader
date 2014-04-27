#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include <QQmlComponent>

#include "rsslist.h"
#include "rssfetcher.h"
#include "recordinfo.h"
#include "recordsmanager.h"
#include "feeddata.h"
#include "downloader.h"
#include "parser.h"
#include "rssapplication.h"


RSSListing::RSSListing(QWidget *parent)
    : QWidget(parent)
{
    fetchButton = new QPushButton(tr("Fetch"), this);
    addButton = new QPushButton(tr("Add Feed"), this);

    treeWidget = new QTreeWidget(this);
    connect(treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
            this, SLOT(itemActivated(QTreeWidgetItem*)));
    QStringList headerLabels;
    headerLabels << tr("Title") << tr("Link") <<tr("Date") << tr("Finished") << tr("Progress");
    treeWidget->setHeaderLabels(headerLabels);
    treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);

    connect(fetchButton, SIGNAL(clicked()), this, SLOT(fetch()));
    connect(addButton, SIGNAL(clicked()), SLOT(addFeed()));

    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *hboxLayout = new QHBoxLayout;


    hboxLayout->addWidget(fetchButton);
    hboxLayout->addWidget(addButton);

    layout->addLayout(hboxLayout);
    layout->addWidget(treeWidget);

    setWindowTitle(tr("RSS listing example"));
    resize(640,480);

    config.load();
}

void RSSListing::closeEvent(QCloseEvent *event)
 {
    config.save();
    event->accept();
 }

void RSSListing::get()
{
    RecordsManager* manager = new RecordsManager(this);
    connect(manager, SIGNAL(recordFinished(RecordInfo*)), SLOT(recordFinished(RecordInfo*)));
    connect(manager, SIGNAL(downloadProgress(RecordInfo*,qint64,qint64)), SLOT(downloadProgress(RecordInfo*,qint64,qint64)));

    int feedCount  = config.feedCount();
    for(int i = 0; i < feedCount; ++i)
    {
        FeedData* feed = config.feedAt(i);
        RssFetcher* fetcher = new RssFetcher(feed);
        connect(fetcher, SIGNAL(finished(QVector<RecordInfo*>)), this, SLOT(finishedEx(QVector<RecordInfo*>)));
        connect(fetcher, SIGNAL(finished(QVector<RecordInfo*>)), manager, SLOT(finishedEx(QVector<RecordInfo*>)));
        fetcher->Fetch(feed->getFeedUrl());
    }
}

void RSSListing::finishedEx(QVector<RecordInfo*> records)
{
    for(auto rec : records)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, rec->getTitle());
        item->setText(1, rec->getUrl());
        item->setText(2, rec->getDate().toString());
        item->setText(3, "Available");
        item->setText(4, "0");
        ++_recordIndex;
        item->setData(0, Qt::UserRole, _recordIndex);
        _hash.insert(rec, _recordIndex);
        treeWidget->addTopLevelItem(item);
    }
}

void RSSListing::recordFinished(RecordInfo* record)
{
    if(!_hash.contains(record))
    {
        qWarning() << "Coulnd't find in hash the record :" << record->getTitle();
        return;
    }
    int index = _hash[record];
    QTreeWidgetItemIterator it(treeWidget);
    while(*it)
    {
        if(index == (*it)->data(0, Qt::UserRole))
        {
            (*it)->setText(3, "Finished");
            return;
        }
        ++it;
    }
}

void RSSListing::downloadProgress(RecordInfo* record, qint64 bytesReceived, qint64 bytesTotal)
{
    if(bytesTotal == 0)
        return;
    if(!_hash.contains(record))
    {
        qWarning() << "Coulnd't find in hash the record :" << record->getTitle();
        return;
    }
    int index = _hash[record];
    QTreeWidgetItemIterator it(treeWidget);
    while(*it)
    {
        if(index == (*it)->data(0, Qt::UserRole))
        {
            if(bytesTotal == -1)
               (*it)->setText(4, "Unknown");
            else
            {
                qint64 progress = 100 * bytesReceived/bytesTotal;
                (*it)->setText(4, QString::number(progress));
            }
            return;
        }
        ++it;
    }
}

void RSSListing::fetch()
{
    fetchButton->setEnabled(false);
    treeWidget->clear();
    get();
}

void RSSListing::addFeed()
{    
    QQmlComponent component(qApp->qmlEngine(), "addFeedDialog.qml");
    QObject* obj = component.create();
    connect(obj, SIGNAL(accepted(QString, QString, QString)), SLOT(feedAccepted(QString, QString, QString)));
}

void RSSListing::feedAccepted(QString url, QString directory, QString prefix)
{
    config.addFeed(url, directory, prefix);
}

void RSSListing::finished()
{
    fetchButton->setEnabled(true);
}

/*
    Open the link in the browser
*/
void RSSListing::itemActivated(QTreeWidgetItem * item)
{
    QDesktopServices::openUrl(QUrl(item->text(1)));
}

void RSSListing::error(QNetworkReply::NetworkError)
{
    qWarning("error retrieving RSS feed");
}
