#include "client.h"

Client::Client(QObject *parent) : QObject(parent), pSock(new ClientSocketAdapter(this)) {
    connect(pSock, SIGNAL(message(QString)), SLOT(on_message(QString)));
}

void Client::send(QString command, QList<QMap<QString, QVariant> > *params) {
    qDebug() << command << ' ' << params << endl;
}

void Client::send(QString command, QMap<QString, QVariant> *params) {
    qDebug() << command << ' ' << params << endl;
}

void Client::sendCommand(QString command, QMap<QString, QVariant> *params) {
    QString streamData;
    foreach (QString key, params->keys()) {
        streamData += key + "->" + params->value(key).toString() + ",";
    }
    pSock->sendString(command + ":" + streamData);
}

void Client::on_message(QString text) {
    qDebug() << text << endl;
}

void Client::on_send() {

}

