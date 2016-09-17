#include "queuebroker.h"
#include <typeinfo>

QueueBroker::QueueBroker(QObject *parent) : QObject(parent) {
    ;
}

void QueueBroker::putMessage(IMessage *message) {

   queue.append(message);
}

void QueueBroker::send(IMessage *message) {
    qDebug() << "Broker: send" << message->toString();
}

void QueueBroker::publishComponents() {
    QString broker = QString("Broker");
    MessageBuilder* mBuild = new MessageBuilder(this);
    mBuild->setSender(broker);
    mBuild->setType(QString("Message"));
    QMap<QString, QVariant> params;

    foreach (ILogic* logic, components.keys()) {
        if (!logic->isPublic())
            continue;
        params[logic->getName()] = logic->getName();
    }

    routeMessage(mBuild->getMessage(broker, QString("registerComponent"), params), QString("Local"));
}

void QueueBroker::registerRemoteSubscribe(QString key, QString sub) {
    QString broker = QString("Broker");
    MessageBuilder* mBuild = new MessageBuilder(this);
    mBuild->setSender(broker);
    mBuild->setType(QString("Message"));
    QMap<QString, QVariant> params;

    params[key] = sub;

    routeMessage(mBuild->getMessage(broker, QString("addSubscribe"), params), QString("Local"));
}

void QueueBroker::registerRemoteComponents(IMessage* msg, QString srcTransport) {
    qDebug() << "Registering remote components from" << srcTransport << msg->toString();
    ITransport* transport = getTransport(srcTransport);
    if (transport) {
        QStringList items = msg->getText().split("::");
        QString command = items[0];
        qDebug() << "Command:" << command;

        if (command == QString("registerComponent")) {
            for (int i = 1; i < items.length(); i++) {

                //addComponentMap(transport, srcTransport + ":" + items[i]);
                QStringList subs = items[i].split(";");
                for (int subI = 0; subI < subs.length(); subI++) {
                    if (subs[subI].length() > 0) {
                        qDebug() << "Register component:" << srcTransport << subs[subI].split("==")[0];
                        addComponentMap(transport, srcTransport + ":" + subs[subI].split("==")[0]);
                    }
                }
            }
        }
        else if (command == QString("addSubscribe")) {
            for (int i = 1; i < items.length(); i++) {
                qDebug() << "Add subscribe:" << srcTransport << items[i];
                QStringList subs = items[i].split("==");
                //foreach (QString key, subs) {
                addSubscribe(subs[1]);
                //}

            }
        }
        else {
            qDebug() << "No command bind for" << command;
        }
    }
    else {
        qDebug() << "No transport found for " << srcTransport;
    }
}

void QueueBroker::routeMessage(IMessage* msg, QString srcTransport) {
    QString dest = msg->getTarget();
    if (dest == QString("Broker")) {
        if (srcTransport == QString("Local")) {
            //foreach (ITransport* dTransport, transports.keys()) {
            qDebug() << "Publish broker message:" << msg->toString();
                //dTransport->send(msg->toString());
            //}
            emit network_message(msg->toString());
        }
        else {
            registerRemoteComponents(msg, srcTransport);
        }
    }
    else {
        QString src = srcTransport + ':' + msg->getSender();
        QString msgType = msg->getType() + ":" + msg->getTarget();
        if (subscribes.contains(src)) {
            QMap<QString, QList<QString>> subscr = subscribes[src];
            if (subscr.contains(msgType)) {
                foreach (QString subDest, subscr[msgType]) {
                    //if (matchMap(dest, subDest)) {
                        // to local or to network?
                        //emit network_message(msg->toString());
                        //if (subDest.split("<").length() == 1)
                        //    subDest = subDest + "<*>";
                        if (componentMap.contains(subDest)) {
                            // TODO: add temp subscribe
                            // QString("Local:Billing;Reply;Local:Local;Persist");
                            if (msg->needResponce()) {
                                QString *tempSubscribe = new QString(subDest + ";" + "Reply" + ";" + src + ";" + "Temp");

                                connect(componentMap[subDest], SIGNAL(message(IMessage*)), componentMap[src], SLOT(emit_message(IMessage*)));

                                addSubscribe(*tempSubscribe);
                            }
                            componentMap[subDest]->receive(msg);
                        }
                        else if (remoteComponents.contains(subDest)) {
                            // emit ?
                            qDebug() << "Sending" << msg->toString() << "to" << subDest;
                            remoteComponents[subDest]->send(msg->toString());
                            //emit network_message(msg->toString());
                        }
                        else
                            qDebug() << "No map for" << msg->toString();
                    //}
                }
            }
        }
    }
}

bool QueueBroker::matchMap(QString src, QString dest) {
    if (src == dest)
        return true;
    else
        return false;
}

void QueueBroker::receive(IMessage *message) {
    qDebug() << "receive(IMessage)" << message->toString();
    if (message->getType() == "Query")
        message = new Query(message);
    routeMessage(message, QString("Local"));
}

void QueueBroker::receive(QString message) {
    IMessage *msg = new IMessage();
    msg->fromString(message);

    QString sourceTransport = ((ITransport*)sender())->getName();
    QString sourceComponent = msg->getSender();
    qDebug() << "receive(QString)" << sourceTransport << ":" << sourceComponent << msg->toString();
    routeMessage(msg, sourceTransport);
}

void QueueBroker::routePacket(Packet* packet) {
    if (packet->destinationTransport == "Local") {
    }
    else
        emit network_message(packet->toString());
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

void QueueBroker::startBroking() {}

void QueueBroker::addComponent(ILogic *component) {
    qDebug() << "Add logic component:" << component->getName() << "[" << components.size() << "]";
    components[component] = component->getName();
    connect(component, SIGNAL(message(IMessage*)), SLOT(receive(IMessage*)));
}

void QueueBroker::addComponent(ITransport *component) {
    qDebug() << "Add transport component:" << component->getName() << "[" << transports.size() << "]";
    transports[component] = component->getName();
    //if (!remoteComponents.contains(component->getName()))
    //    remoteComponents[component->getName()] = component;
    //if (component->getName() == "Local")
    //    connect(component, SIGNAL(message(QString)), SLOT(receive(QString)));
}

void QueueBroker::addComponent(PluginInterface *component, QMap<QString, QVariant> params) {
    qDebug() << params;
    ILogic* lcom = dynamic_cast<ILogic *>(component);
    if (lcom) {
        addComponent(lcom);
    }
    ITransport* tcom = dynamic_cast<ITransport *>(component);
    if (tcom) {
        addComponent(tcom);
    }
    qDebug() << typeid(*component).name();
}

QString QueueBroker::getMapName(ITransport *transport, ILogic *component) {
    QString addr = transport->getAddress();
    QString name;
    if (addr.length() > 1)
        name = transport->getName() + "<" + addr + ">";
    else {
        name = transport->getName();
        if (name != "Local") name += "<*>";
    }
    name = name + ":" + component->getName();
    return name;
}

void QueueBroker::addComponentMap(ITransport *transport, ILogic *component) {
    QString name = getMapName(transport, component);
    if (!componentMap.contains(name))
        if (transport->isLocal()) {
            qDebug() << "Add component map:" << name;
            componentMap[name] = component;
        }
    else
        qDebug() << sender() << ":" << name << "already in component map";
}

void QueueBroker::addComponentMap(ITransport *transport, QString component) {
    if (!remoteComponents.contains(component))
        if (!transport->isLocal())
            remoteComponents[component] = transport;
    else
        qDebug() << sender() << ":" << component << "already in component map";
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

    QString src = items[0];
    QString msg = items[1];
    QString dst = items[2];
    bool persist;
    if (items[3] == QString("Persist"))
        persist = true;
    else
        persist = false;
    QMap<QString, QList<QString>> subItems;
    if (subscribes.contains(src)) {
        subItems = subscribes[src];
    }

    if (subItems.contains(msg)) {
        if (!subItems[msg].contains(dst))
            subItems[msg].append(dst);
    }
    else {
        QList<QString> subDest;
        subDest.append(dst);
        subItems[msg] = subDest;
    }
    subscribes[src] = subItems;
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
    else {
        foreach (ITransport* key, transports.keys()) {
            QString tAddr = key->getName();
            qDebug() << tAddr;
            if (tAddr == transport)
                nTransport = key;
        }
    }
    return nTransport;
}
