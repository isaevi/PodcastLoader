#ifndef HELPERINTERFACES_H
#define HELPERINTERFACES_H

#include <QList>
class FeedData;

class IFeedInformationFetcher {
public:
    virtual void resetQueue(QList<FeedData*> feeds) = 0;
    virtual void addFeedToQueue(FeedData* feed) = 0;
};

#endif // HELPERINTERFACES_H
