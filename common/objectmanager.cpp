#include "objectmanager.h"

ObjectManager::ObjectManager(QObject *parent) : QObject(parent), broker(new QueueBroker(this)) {

}


void ObjectManager::addComponent(ILogic *component) {
    qDebug() << components.size();
    components.append(component);
}

void ObjectManager::addComponent(ITransport *component) {
    qDebug() << transports.size();
    transports.append(component);
}

void ObjectManager::startBroking() {
    broker->startBroking();
}

void ObjectManager::addSubscribe(QString &subscribe) {
    QStringList items = subscribe.split(",");
    ITransport* sourceTransport = getTransport(items[0]);
    ILogic* sourceComponent = getLogic(items[1]);
    IMessage* messageType = getMessage(items[2]);
    ITransport* destinationTransport = getTransport(items[3]);
    ILogic* destinationComponent = getLogic(items[4]);
    //foreach (QString item, items) {
    //    qDebug() << item;
    //}

    broker->subscribe(sourceTransport, sourceComponent, messageType, destinationTransport, destinationComponent);
}

ILogic* ObjectManager::getLogic(QString &logic) {
    ILogic* nLogic = 0;
    for (int i=0; i < components.length(); i++) {
        if (components[i]->getName() == logic)
            nLogic = components[i];
    }
    return nLogic;
}

IMessage* ObjectManager::getMessage(QString &messageType) {
    IMessage* message = 0;
    return message;
}

ITransport* ObjectManager::getTransport(QString &transport) {
    ITransport* nTransport = 0;
    if (transport == "Local")
        nTransport = new ITransport(this);
    else if (transport == "Network")
        nTransport = transports[0];
    else {
        QStringList titems = transport.split(":");
        if (titems.length() > 1) {
            QString addr = titems[1];
            for (int i=0; i < transports.length(); i++) {
                QString tAddr = transports[i]->getAddress();
                if (tAddr.length() > 0) {
                    if (addr == ("<" + tAddr + ">"))
                        nTransport = transports[i];
                }
            }
        }
    }
    return nTransport;
}

