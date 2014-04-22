#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include "recordinfo.h"

class QString;
class QNetworkReply;

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    virtual ~Downloader();
    bool get(RecordInfo *rec);
    bool isBusy() const {return _isBusy;}
    void setBusy() {_isBusy = true;}

    void PrepareDirectory(QString title);
signals:
    void downloaded(RecordInfo* rec);
    void errorHappen();

private slots:
    void finished();

private:
    RecordInfo* _rec;
    QNetworkReply* _reply;
    bool _isBusy;
};

#endif // DOWNLOADER_H
