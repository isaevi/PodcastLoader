#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>

#include "rsslist.h"
#include "rssfetcher.h"
#include "recordinfo.h"
#include "recordsmanager.h"
#include "feeddata.h"
#include "downloader.h"
#include "parser.h"


RSSListing::RSSListing(QWidget *parent)
    : QWidget(parent)
{
    fetchButton = new QPushButton(tr("Fetch"), this);

    treeWidget = new QTreeWidget(this);
    connect(treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
            this, SLOT(itemActivated(QTreeWidgetItem*)));
    QStringList headerLabels;
    headerLabels << tr("Title") << tr("Link") <<tr("Date");
    treeWidget->setHeaderLabels(headerLabels);
    treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(fetchButton, SIGNAL(clicked()), this, SLOT(fetch()));

    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *hboxLayout = new QHBoxLayout;


    hboxLayout->addWidget(fetchButton);

    layout->addLayout(hboxLayout);
    layout->addWidget(treeWidget);

    setWindowTitle(tr("RSS listing example"));
    resize(640,480);
}

void RSSListing::get()
{
    QVector<FeedData> feeds;
    feeds.push_back(FeedData("http://learningenglish.voanews.com/podcast/?count=3&zoneId=3521", "C:\\Podcast\\aii", "aii"));
    feeds.push_back(FeedData("http://learningenglish.voanews.com/podcast/?count=3&zoneId=986", "C:\\Podcast\\am", "am"));
    feeds.push_back(FeedData("http://learningenglish.voanews.com/podcast/?count=3&zoneId=1577", "C:\\Podcast\\itn", "itn"));
    feeds.push_back(FeedData("http://learningenglish.voanews.com/podcast/?count=3&zoneId=1579", "C:\\Podcast\\sitn", "sitn"));
    feeds.push_back(FeedData("http://learningenglish.voanews.com/podcast/?count=3&zoneId=1580", "C:\\Podcast\\tia", "tia"));
    feeds.push_back(FeedData("http://learningenglish.voanews.com/podcast/?count=3&zoneId=987", "C:\\Podcast\\wats", "wats"));

    RecordsManager* manager = new RecordsManager(this);

    for(auto feed : feeds){
        RssFetcher* fetcher = new RssFetcher(feed);
        connect(fetcher, SIGNAL(finished(QVector<RecordInfo*>)), this, SLOT(finishedEx(QVector<RecordInfo*>)));
        connect(fetcher, SIGNAL(finished(QVector<RecordInfo*>)), manager, SLOT(finishedEx(QVector<RecordInfo*>)));
        fetcher->Fetch(feed.getFeedUrl());
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
        treeWidget->addTopLevelItem(item);
    }
}

void RSSListing::fetch()
{
    fetchButton->setEnabled(false);
    treeWidget->clear();
    get();
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
