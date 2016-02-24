#include "queuebroker.h"

QueueBroker::QueueBroker(QObject *parent) : IQueueBroker(parent) {

}

void QueueBroker::putMessage(IMessage *message) {
    queue.append(message);
}

void QueueBroker::send(IMessage *message) {

}

void QueueBroker::receive(IMessage *message) {
    Packet pkg;
    QString sender = message->getSender();
    QString target = message->getTarget();
    pkg.sourceTransport = QString("Local");
    pkg.sourceComponent = sender;
    pkg.destinationComponent = target;
    pkg.destinationTransport = transports[remoteComponents[target]];
    pkg.msg = message;
    qDebug() << "receive(IMessage)" << pkg.toString();
}

void QueueBroker::receive(QString message) {
    qDebug() << "receive(QString)" << message;
}

void QueueBroker::subscribe(
        ITransport &sourceTransport,
        ILogic &sourceComponent,
        IMessage &messageType,
        ITransport &destinationTransport,
        ILogic &destinationComponent)
{
    qDebug() << "subscribe()" << endl;
    qDebug() << sourceTransport.getName() << ":" << sourceComponent.getName();
    qDebug() << messageType.getName();
    qDebug() << destinationTransport.getName() << ":" << destinationComponent.getName();
}

void QueueBroker::startBroking() {

}

void QueueBroker::addComponent(ILogic *component) {
    qDebug() << components.size();
    components[component] = component->getName();
    connect(component, SIGNAL(message(IMessage*)), SLOT(receive(IMessage*)));
}

void QueueBroker::addComponent(ITransport *component) {
    qDebug() << transports.size();
    transports[component] = component->getName();
    connect(component, SIGNAL(message(QString)), SLOT(receive(QString)));
}

void QueueBroker::addComponentMap(ITransport *transport, ILogic *component) {

}

void QueueBroker::removeComponent(ITransport *component) {
    transports.remove(component);
}

void QueueBroker::removeComponent(ILogic *component) {
    components.remove(component);
}

QMap<ITransport *, ILogic *> QueueBroker::getComponentMap(QString &pair) {
    QStringList items = pair.split(":");
    ITransport* transport = getTransport(items[0]);
    ILogic* logic = new ILogic(this);
    if (transport->isLocal())
        logic = getLogic(items[1]);
    else {
        // Find component in remote components
        if (remoteComponents.contains(items[1])) {
            logic = new ILogic(this);
        }
    }
    logic->setName(items[1]);
    QMap<ITransport *, ILogic *> map;
    map.insert(transport, logic);
    return map;
}

void QueueBroker::addSubscribe(QString &subscribe) {
    QStringList items = subscribe.split(";");

    /*
    QMap<ITransport *, ILogic *> sourceMap = getComponentMap(items[0]);
    foreach (ITransport key, sourceMap.values()) {
        if (key.isLocal())
            ILogic* sourceComponent = getLogic(items[1]);
        else {

        }
    }


    IMessage* messageType = getMessage(items[2]);

    ITransport* destinationTransport = getTransport(items[3]);
    if (destinationTransport->isLocal())
        ILogic* destinationComponent = getLogic(items[4]);
    else {
        ILogic* destinationComponent = new ILogic(this);
    }
    //foreach (QString item, items) {
    //    qDebug() << item;
    //}

    //subscribe(sourceTransport, sourceComponent, messageType, destinationTransport, destinationComponent);
    */
    qDebug() << "subscribe()" << subscribe;
}

ILogic* QueueBroker::getLogic(QString &logic) {
    ILogic* nLogic = 0;
    foreach (ILogic* key, components.keys()) {
        if (key->getName() == logic)
            nLogic = key;
    }
    return nLogic;
}

IMessage* QueueBroker::getMessage(QString &messageType) {
    IMessage* message = 0;
    return message;
}

ITransport* QueueBroker::getTransport(QString &transport) {
    ITransport* nTransport = 0;
    if (transport == "Local")
        nTransport = new ITransport(this);
    //else if (transport == "Network")
    //    nTransport = transports[0];
    else {
        QStringList titems = transport.split(":");
        if (titems.length() > 1) {
            QString addr = titems[1];
            foreach (ITransport* key, transports.keys()) {
                QString tAddr = key->getAddress();
                if (tAddr.length() > 0) {
                    if (addr == ("<" + tAddr + ">"))
                        nTransport = key;
                }
            }
        }
    }
    return nTransport;
}
