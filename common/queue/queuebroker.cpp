#include "queuebroker.h"
#include <typeinfo>


QueueBroker::QueueBroker(QObject *parent) : QObject(parent) {
    QString subscr = QString("Broker;Broker;*;*");
    addSubscribe(subscr);
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

    foreach (ILogic* logic, components.values()) {
        if (!logic->isPublic())
            continue;
        params[logic->getName()] = logic->getName();
    }

    routeMessage(mBuild->getMessage(broker, QString("registerComponent"), params), QString("Local"));
}

QList<Subscribe *> QueueBroker::searchSubscribes(QString source, QString mType) {
    // [transport_name[<address:port>|<*>]::]component_name[<self_name[:{instance_id|thread_id}>]]
    QStringList comp = source.split("::");
    Subscribe *subscr = new Subscribe();
    QString transport;
    QString component;
    if (comp.length() == 1) {
        // без транспортной, по умолчанию берем локальный транспорт и нормализуем до transport_name<*>
        transport = subscr->normalizeAddress(QString(""));
        component = subscr->normalizeComponentName(comp[0]);
    }
    else {
        transport = subscr->normalizeAddress(comp[0]);
        component = subscr->normalizeComponentName(comp[1]);
    }
    QString nSource = transport + "::" + component;
    QList<Subscribe *> subs;
    // точные совпадения
    if (subscribes.contains(nSource)) {
        QMap<QString, QMap<QString, Subscribe *>> subsMatch = subscribes[nSource];
        if (subsMatch.contains(mType)) {
            // find temp matches (e.g. Query<hash> for reply)
            foreach (Subscribe *sub , subsMatch[mType].values()) {
                subs.append(sub);
            }
        }
        if (subsMatch.contains("*")) {
            // find all matches
            foreach (Subscribe *sub , subsMatch[QString("*")].values()) {
                subs.append(sub);
            }
        }
        if (mType.contains("<") && mType.contains(">")) {
            // find persistant matches
            QString pType = mType.split("<")[0];
            if (subsMatch.contains(pType)) {
                // find temp matches (e.g. Query<hash> for reply)
                foreach (Subscribe *sub , subsMatch[(pType)].values()) {
                    subs.append(sub);
                }
            }
        }
    }
    return subs;
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
    Subscribe * tSub = new Subscribe;
    QString dCom = tSub->normalizeComponentName(msg->getTarget());
    QString sTran = tSub->normalizeAddress(srcTransport);
    qDebug() << "routeMessage" << msg->toString() << "from" << sTran << "to" << dCom;

    // search subscribe by message source
    QList<Subscribe *> subs = searchSubscribes(msg->getSender(), msg->getType());
    qDebug() << "Found subscribes:" << subs.length();
    foreach (Subscribe *subscr, subs) {
        qDebug() << subscr->getDestination();
        if (sTran + "::" + dCom == subscr->getDestination()) {
            qDebug() << "Matched subscription" << subscr->toString() << msg->toString();
            QList<ITransport *> dTrans = getTransports(subscr->getDestinationTransport());
            if (dTrans.length() > 0) {
                foreach (ITransport *transport, dTrans) {
                    if (transport->isLocal()) {
                        ILogic *dComp = getLogic(dCom);
                        if (dComp)
                            dComp->receive(msg);
                    }
                    else {
                        Packet *pkt = new Packet();
                        pkt->setDestinationAddress(transport->getAddress());
                        //pkt->setSourceAddress(sTran);
                        pkt->setData(msg->toString());
                        emit message(pkt);
                    }
                }
            }
            else {
                qDebug() << "No transports found";
            }
        }
    }

    /*
    if (dest == QString("Broker")) {
        if (srcTransport == QString("Local")) {
            //foreach (ITransport* dTransport, transports.keys()) {
            qDebug() << "Publish broker message:" << msg->toString();
                //dTransport->send(msg->toString());
            //}
            emit message(msg->toString());
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
    */
}

QList<ITransport *> QueueBroker::getTransports(QString trName) {
    QList<ITransport *> trs;
    if (
            ((trName.contains("<") && trName.contains(">")) && trName.contains("<*>"))
            || !(trName.contains("<") && trName.contains(">"))
        ){
        foreach (ITransport *tr, transports)
            trs.append(tr);
    }
    else {
        if (transports.contains(trName))
            trs.append(transports[trName]);
    }
    return trs;
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

void QueueBroker::receive(Packet *pkt) {
    IMessage* msg = new IMessage();
    msg->fromString(pkt->getData());
    receive(msg);
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
    /*
    if (packet->destinationTransport == "Local") {
    }
    else
        emit network_message(packet->toString());
    */
}

void QueueBroker::startBroking() {}

void QueueBroker::addComponent(ILogic *component) {
    qDebug() << "Add logic component:" << component->getName() << "[" << components.size() << "]";
    components[Subscribe::normalizeComponentName(component->getName())] = component;
    connect(component, SIGNAL(message(IMessage*)), SLOT(receive(IMessage*)));
}

void QueueBroker::addComponent(ITransport *component) {
    qDebug() << "Add transport component:" << component->getName() << "[" << transports.size() << "]";
    QString sub;
    if (component->isLocal())
        sub = QString("Broker;Broker;*;*");
    else
        sub = QString("Network::Broker;Broker;*;*");
    addSubscribe(sub);
    QString normName = Subscribe::normalizeAddress(component->getName());
    transports[normName] = component;
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
        lcom->setParent(this);
        lcom->setInitParams(&params);
    }
    ITransport* tcom = dynamic_cast<ITransport *>(component);
    if (tcom) {
        addComponent(tcom);
        tcom->setParent(this);
        tcom->setInitParams(&params);
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

    transports.remove(Subscribe::normalizeAddress(component->getName()));
}

void QueueBroker::removeComponent(ILogic *component) {

    components.remove(Subscribe::normalizeComponentName(component->getName()));
}

/*
QMap<ITransport *, ILogic *> QueueBroker::getComponentMap(QString &pair) {
    QStringList items = pair.split(":");
    ITransport* transport = getTransport(items[0]);
    ILogic* logic; // = new ILogic(this);
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
*/

void QueueBroker::addSubscribe(QString &subscribe) {
    qDebug() << "addSubscribe()" << subscribe;
    Subscribe* sub = new Subscribe(subscribe);
    qDebug() << "Subscription processed:" << sub->toString();
    QString src = sub->getSource();
    QMap<QString, Subscribe *> sub_hash;
    sub_hash[sub->hash()] = sub;
    QString mtype = sub->getType();
    // source
    if (subscribes.contains(src)) {
        // message_type
        if (subscribes[src].contains(mtype)) {
            if (!subscribes[src][mtype].contains(sub->hash())) {
                subscribes[src][mtype][sub->hash()] = sub;
            }
            else {
                qDebug() << "Subscription already exists" << sub->toString();
            }
        }
        else {
            subscribes[src][mtype] = sub_hash;
        }
    }
    else {
        QMap<QString, QMap<QString, Subscribe *>> nmtype;
        nmtype[mtype] = sub_hash;
        subscribes[src] = nmtype;
    }
}

ILogic* QueueBroker::getLogic(QString &logic) {
    ILogic* nLogic = 0;
    foreach (ILogic* key, components.values()) {
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
        foreach (ITransport* key, transports.values()) {
            QString tAddr = key->getName();
            qDebug() << tAddr;
            if (tAddr == transport)
                nTransport = key;
        }
    }
    return nTransport;
}
