#include "logicqueuebroker.h"
#include "imessage.h"

#include <QStringList>
#include <QDebug>

#include "queuebroker.h"
#include "uri.h"

LogicQueueBroker::LogicQueueBroker(QObject *parent) : ILogic(parent) {

}

void LogicQueueBroker::receive(IMessage *msg) {
    qDebug() << "Broker receive message" << msg->toString();

    QStringList msgParts = msg->getText().split("::");
    if (msgParts[0] == "registerComponent") {
        QStringList comps = msgParts[1].split(";");
        foreach (QString comp, comps) {
            if (comp.length() > 0 ) {
                QString rAddr = msg->getSender().getAddress();
                qDebug() << "Register remote component" << comp << rAddr;
                m_broker->registerRemoteComponent(comp.split("==")[0], rAddr);
                //qDebug() << "Component for register (obsolete, no action)" << comp;
            }
        }
    }
    /*
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

void LogicQueueBroker::on_init_complete() {
    m_broker = static_cast<QueueBroker*>(this->parent());
    QStringList subscribes;
    subscribes << "Network<*>::Broker<*>;Broker;Message;Persist";
    foreach (QString subscribe, subscribes)
        m_broker->addSubscribe(subscribe);
}
