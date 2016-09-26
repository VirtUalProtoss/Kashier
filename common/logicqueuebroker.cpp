#include "logicqueuebroker.h"
#include "imessage.h"

#include <QStringList>
#include <QDebug>

#include "uri.h"

LogicQueueBroker::LogicQueueBroker(QObject *parent) : ILogic(parent) {

}

void LogicQueueBroker::receive(IMessage *msg) {
    qDebug() << "Broker receive message" << msg->toString();
    /*
    QStringList msgParts = msg->getText().split("::");
    if (msgParts[0] == "registerComponent") {
        QStringList comps = msgParts[1].split(";");
        foreach (QString comp, comps) {
            qDebug() << "Component for register (obsolete, no action)" << comp;
        }
    }
    if (msgParts[0] == "addSubscribe") {
        QStringList comps = msgParts[1].split(";");
        foreach (QString comp, comps) {
            QString srcTransport = URI::getTransport(msg->getSender());
            QString srcComponent = comp.split("==")[1];
            m_broker->addSubscribe();
        }
    }
    */
    if (msg->getType() == "Message") {

    }
    if (msg->getType() == "Query") {

    }
    if (msg->getType() == "Reply") {

    }
    if (msg->getType() == "RPC") {

    }
}
