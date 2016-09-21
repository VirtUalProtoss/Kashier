#include "queuebroker.h"
#include <typeinfo>

#include "uri.h"

QueueBroker::QueueBroker(QObject *parent) : QObject(parent) {
    //QString subscr = QString("Broker;Broker;*;*");
    //addSubscribe(subscr);
}

void QueueBroker::putMessage(IMessage *message) {

   queue.append(message);
}

void QueueBroker::send(IMessage *message) {
    qDebug() << "Broker: send" << message->toString();
}

void QueueBroker::publishComponents(QString transport, QString target) {
    QList<ITransport *> dstTransports = getTransports(transport);
    foreach (ITransport *dstTransport, dstTransports) {
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
        if (params.count() > 0) {
            IMessage *msg = mBuild->getMessage(target, QString("registerComponent"), params);
            emit message(dstTransport, msg);
        }
        else {
            qDebug() << "No components to publish found";
        }
    }
}

void QueueBroker::removeSubscriptions(QString dstTransportName) {
    // TODO: remove all subscriptions, for destination with dstTransportName
}

QList<Subscribe *> QueueBroker::searchSubscribes(QString source, QString mType) {
    // [transport_name[<address:port>|<*>]::]component_name[<self_name[:{instance_id|thread_id}>]]
    QStringList comp = source.split("::");
    QString transport;
    QString component;
    if (comp.length() == 1) {
        // без транспортной, по умолчанию берем локальный транспорт и нормализуем до transport_name<*>
        transport = URI::normalizeAddress(QString(""));
        component = URI::normalizeComponentName(comp[0]);
    }
    else {
        transport = URI::normalizeAddress(comp[0]);
        component = URI::normalizeComponentName(comp[1]);
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

void QueueBroker::processBrokerMessage(IMessage *msg, ITransport *srcTransport) {
    //QList<ITransport *> srcTransports = getTransports(srcTransportName);
    registerRemoteComponents(msg, srcTransport->getName());
}

void QueueBroker::routeMessage(IMessage* msg, QString sourceTransport) {
    QString srcComponentName = URI::normalizeComponentName(msg->getSender());
    QString dstComponentName = URI::normalizeComponentName(msg->getTarget());
    QString srcTransportName = URI::normalizeAddress(sourceTransport);

    QString srcFullName = srcTransportName + "::" + srcComponentName;

    qDebug() << "routeMessage" << msg->toString() << "from" << srcFullName << "to" << dstComponentName;

    // search subscribe by message source
    QList<Subscribe *> foundedSubscriptions = searchSubscribes(msg->getSender(), msg->getType());
    qDebug() << "Found subscribes:" << foundedSubscriptions.length();

    foreach (Subscribe *subscr, foundedSubscriptions) {

        if (srcTransportName + "::" + dstComponentName == subscr->getDestination()) {

            qDebug() << "Matched subscription" << subscr->toString() << msg->toString();

            QList<ITransport *> dstTransports = getTransports(subscr->getDestinationTransport());

            if (dstTransports.length() > 0) {
                foreach (ITransport *trDest, dstTransports) {
                    if (trDest->isLocal()) {
                        // Немного грязных хаков TODO: remove this shit
                        if (URI::getComponent(dstComponentName) == QString("Broker")) {
                            foreach (ITransport *srcTransport, getTransports(srcTransportName)) {
                                processBrokerMessage(msg, srcTransport);
                            }
                        }
                        else {
                            ILogic *dComp = getLogic(dstComponentName);
                            if (dComp)
                                dComp->receive(msg);
                        }
                    }
                    else {
                        Packet *pkt = new Packet();
                        pkt->setDestinationAddress(trDest->getAddress());
                        pkt->setData(msg->toString());
                        emit message(pkt);
                    }
                }
            }
            else {
                qDebug() << "No transports found, broken config?";
            }
        }

    }
}

QList<ITransport *> QueueBroker::getTransports(QString trName) {
    QList<ITransport *> trs;
    if (
            ((trName.contains("<") && trName.contains(">")) && trName.contains("<*>"))
            || !(trName.contains("<") && trName.contains(">"))
        ){
        foreach (ITransport *tr, transports) {
            if (tr->getName().split("<")[0] == trName.split("<")[0])
                trs.append(tr);
        }
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

void QueueBroker::receive(Packet *pkt, QString source) {
    IMessage* msg = new IMessage();
    msg->fromString(pkt->getData());
    routeMessage(msg, source);
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

void QueueBroker::startBroking() {

}

void QueueBroker::addComponent(ILogic *component) {
    qDebug() << "Add logic component:" << component->getName() << "[" << components.size() << "]";
    components[URI::normalizeComponentName(component->getName())] = component;
    connect(component, SIGNAL(message(IMessage*)), SLOT(receive(IMessage*)));
}

void QueueBroker::addComponent(ITransport *component) {
    qDebug() << "Add transport component:" << component->getName() << "[" << transports.size() << "]";
    /*
    QString sub;
    if (component->isLocal())
        sub = QString("Broker;Broker;*;*");
    else
        sub = QString("Network::Broker;Broker;*;*");
    addSubscribe(sub);
    */
    //QString normName = URI::normalizeAddress(component->getName());
    if (!transports.contains(component->getName()))
        transports[component->getName()] = component;
    //if (!remoteComponents.contains(component->getName()))
    //    remoteComponents[component->getName()] = component;
    //if (component->getName() == "Local")
    //    connect(component, SIGNAL(message(QString)), SLOT(receive(QString)));
}

void QueueBroker::addComponent(PluginInterface *component, QMap<QString, QVariant> params) {
    qDebug() << params;
    ILogic* lcom = dynamic_cast<ILogic *>(component);
    if (lcom) {
        lcom->setParent(this);
        lcom->setInitParams(&params);
        addComponent(lcom);
    }
    ITransport* tcom = dynamic_cast<ITransport *>(component);
    if (tcom) {
        tcom->setParent(this);
        tcom->setInitParams(&params);
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

    transports.remove(URI::normalizeAddress(component->getName()));
}

void QueueBroker::removeComponent(ILogic *component) {

    components.remove(URI::normalizeComponentName(component->getName()));
}

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
