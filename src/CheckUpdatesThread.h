#ifndef CHECKUPDATESTHREAD_H
#define CHECKUPDATESTHREAD_H

#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QDomDocument>


class CheckUpdatesThread : public QThread
{
    Q_OBJECT
public:
    explicit CheckUpdatesThread(QObject *parent = 0);

private:
    QNetworkAccessManager* manager;
    QObject *parent;
    volatile bool isUpdateAvailable;


protected:
    void run();
    
signals:
    
private slots:
    void replyFinished(QNetworkReply* reply);
    
};

#endif // CHECKUPDATESTHREAD_H
