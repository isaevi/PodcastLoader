#ifndef FEEDDATA_H
#define FEEDDATA_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QSet>
#include <QMutex>

class FeedData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix NOTIFY prefixChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool empty READ empty WRITE setEmpty NOTIFY emptyChanged)
public:
    FeedData(QObject* parent = nullptr) : QObject(parent), _empty(true) {}
    FeedData(QString feedTitle, QString feedUrl, QString feedDir, QString feedPrefix, QObject *parent);

    void addProcessedGuid(const QString &guid);
    bool isContainsAmongProcessed(const QString& guid);
    QSet<QString> getProcessedGuids();
    QUrl url() const;
    QString dir() const;
    QString prefix() const;
    QString title() const;    
    bool empty() const;
public slots:
    void setUrl(QUrl arg);
    void setDir(QString arg);
    void setPrefix(QString arg);
    void setTitle(QString arg);
    void setEmpty(bool arg);

signals:
    void urlChanged(QUrl arg);
    void dirChanged(QString arg);
    void prefixChanged(QString arg);
    void titleChanged(QString arg);
    void emptyChanged(bool arg);

private:
    QSet<QString> _processedGuids;
    QMutex _mutex;
    QUrl _url;
    QString _dir;
    QString _prefix;
    QString _title;
    bool _empty;
};

#endif // FEEDDATA_H
