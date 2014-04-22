#include <QtWidgets>

#include "rssapplication.h"
#include "rsslist.h"

int main(int argc, char **argv)
{    
    RssApplication app(argc, argv);
    RSSListing *rsslisting = new RSSListing;
    rsslisting->show();
    return app.exec();
}
