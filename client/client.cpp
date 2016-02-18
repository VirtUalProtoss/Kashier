#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent),
    pSock(new ClientSocketAdapter(this)),
    broker(new QueueBroker(this))
{
    connect(pSock, SIGNAL(message(QString)), SLOT(on_message(QString)));
}

void Client::send(QString command, QList<QMap<QString, QVariant> > *params) {
    qDebug() << command << ' ' << params << endl;
}

void Client::send(QString command, QMap<QString, QVariant> *params) {
    qDebug() << command << ' ';
    foreach (QString key, params->keys()) {
        qDebug() << key + ":" + params->value(key).toString() + ", ";
    }
    qDebug() << endl;
}

void Client::initComponents() {
    ILogic* kkm = new KKM(this);
    ILogic* local = new Local(this);
    ILogic* gui = new GUI(this);
//    ITransport* tLocal = new ITransport(this);
    broker->addComponent(kkm);
    broker->addComponent(local);
    broker->addComponent(gui);
    broker->addComponent(pSock);
//    broker->addComponentMap(tLocal, kkm);
//    broker->addComponentMap(tLocal, local);
//    broker->addComponentMap(tLocal, gui);
}

void Client::prepareSubcribes() {
    QStringList subscribes;
    subscribes << QString("Local:GUI;Query:Billing;Network<127.0.0.1>:Billing;Persist");
    subscribes << QString("Local:GUI;Query:KKM;Local:Local;Persist");
    subscribes << QString("Network:Billing;Reply;Local:Local;Persist");
    subscribes << QString("Local:KKM;Reply;Local:Local;Persist");
    foreach (QString subscribe, subscribes)
        broker->addSubscribe(subscribe);
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

