#include "CheckUpdatesThread.h"
#include "MainWindow.h"

CheckUpdatesThread::CheckUpdatesThread(QObject *parent) : QThread(parent) {
    isUpdateAvailable = false;
    this->parent = parent;manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    // Check two destinations to have more reliability
    manager->get(QNetworkRequest(QUrl("http://cloud.github.com/downloads/Y-Vladimir/SmartDeblur/updates.xml")));
    manager->get(QNetworkRequest(QUrl("http://yuzhikov.com/updates.xml")));

}

void CheckUpdatesThread::run() {
    qDebug() << "CheckUpdatesThread started";
}

void CheckUpdatesThread::replyFinished(QNetworkReply * reply) {
    try {
        if (reply->error() != QNetworkReply::NoError) {
            reply->deleteLater();
            return;
        }

        QDomDocument updatesDoc("updatesXML");
        updatesDoc.setContent(QString(reply->readAll()));
        reply->deleteLater();

        QDomElement appElem = updatesDoc.documentElement();
        QString lastVersion = appElem.attributeNode("lastVersion").nodeValue();
        QString description = appElem.elementsByTagName("description").at(0).toElement().text();
        QString date = appElem.elementsByTagName("date").at(0).toElement().text();
        QString url = appElem.elementsByTagName("url").at(0).toElement().text();
        QString changes;
        QDomNodeList nodeList = appElem.elementsByTagName("changes").at(0).toElement().elementsByTagName("item");
        if (nodeList.count() > 0) {
            for(int i=0; i<nodeList.count(); i++) {
                changes += "<li>" + nodeList.at(i).toElement().text() + "</li>";
            }
            changes = "<ul>"+changes+"</ul>";
        }

        // If gathered vesrion not equal current, then show message
        if (lastVersion.length() > 1 && lastVersion != MainWindow::appVersion) {
            if (isUpdateAvailable) {
                return;
            }
            isUpdateAvailable = true;
            QString updateText = "Your installed version of SmartDeblur is %1<b><br>"
                    "An updated version (%2, from %3) is available!</b><br><br>"
                    "%4%5"
                    "Download a new version by the following link:<br>"
                    "<a href=\"%6\">%6</a>";
            QMessageBox::information((QWidget*)parent, tr("New version of SmartDblur"),
                                     updateText.arg(MainWindow::appVersion, lastVersion, date, description, changes, url));
        }
    } catch (...) {
        qDebug() << "ERROR while checking updates!";
    }

}
