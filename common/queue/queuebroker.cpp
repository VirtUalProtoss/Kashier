#include "queuebroker.h"

#include <typeinfo>

#include "uri.h"

QueueBroker::QueueBroker(QObject *parent) : QObject(parent) {
    LogicQueueBroker* m_lq_broker = new LogicQueueBroker(this);
    addComponent(m_lq_broker);
}

void QueueBroker::publishComponents(QString transport, QString target) {
    QList<ITransport *> dstTransports = getTransports(transport);
    foreach (ITransport *dstTransport, dstTransports) {
        QString broker = QString("Broker");
        MessageBuilder* mBuild = new MessageBuilder(this);
        mBuild->setSender(broker);
        mBuild->setType(QString("Message"));
        QMap<QString, QVariant> params;

        foreach (ILogic* logic, m_components.values()) {
            if (!logic->isPublic())
                continue;
            // params[componentCommonName] = componentFullName (with address)
            params[URI::getComponent(logic->getName())] = logic->getName();
        }
        if (params.count() > 0) {
            IMessage *msg = mBuild->getMessage(target + QString("::") + broker, QString("registerComponent"), params);
            send(dstTransport, msg);
        }
        else {
            qDebug() << "No components to publish found";
        }
    }
}

void QueueBroker::removeSubscribes(QString dstTransportName) {
    // TODO: remove all subscriptions, for destination with dstTransportName
}

void QueueBroker::addTempSubscribe(Subscribe &sub, IMessage &msg) {
    if (msg.getType() == "Query") {
        QString src = msg.getTarget();
        QString dst = msg.getSender();
        Query *qMsg = new Query(msg);
        QString hash = qMsg->getHash();
        QString subscr = QString(src + ";" + dst + ";" + "Reply<" + hash + ">;Temp");

        addSubscribe(subscr);
    }
}

ILogic *QueueBroker::getLogic(QString logic) {
    ILogic* nLogic = 0;
    foreach (ILogic* key, m_components.values()) {
        if (URI::normalizeComponentName(key->getName()) == logic)
            nLogic = key;
    }
    return nLogic;
}

ITransport* QueueBroker::getTransport(QString transport) {
    ITransport* nTransport = 0;
    if (transport == "Local")
        nTransport = new ITransport(this);
    else {
        foreach (ITransport* key, m_transports.values()) {
            QString tAddr = key->getName();
            qDebug() << tAddr;
            if (tAddr == transport)
                nTransport = key;
        }
    }
    return nTransport;
}

QList<Subscribe *> QueueBroker::searchSubscribes(QString source, QString mType) {
    // [transport_name[<address:port>|<*>]::]component_name[<self_name[:{instance_id|thread_id}>]]
    QString sender = URI::normalizeAddress(URI::getTransport(source));
    QString component = URI::normalizeComponentName(URI::getComponent(source));

    QList<Subscribe *> subs;
    bool matched = false;
    foreach (Subscribe* sub, m_subscribes) {

        if (sub->getType() != URI::normalizeComponentName(mType))
            continue;

        matched = false;
        QString subSource = sub->getSource();
        QString subSender = URI::getTransport(subSource);
        QString subComponent = URI::getComponent(subSource);
        // точные совпадения
        if (subSource == sender + QString("::") + component)
            matched = true;
        QString nComp = URI::normalizeComponentName(URI::getName(component));
        // совпадения по типу компонента
        if (sub->getType() != "Reply") {
            if (subSender == sender) {
                // точное совпадение транспорта
                if (subComponent == component)
                    matched = true;
                if (URI::normalizeComponentName(subComponent) == nComp)
                    matched = true;
            }
            else if (URI::getName(subSender) == URI::getName(sender)) {
                // совпадение по всем транспортам
                if (subComponent == component)
                    matched = true;
                if (URI::normalizeComponentName(subComponent) == nComp)
                    matched = true;
            }
            else if (subSender == "*") {
                if (subComponent == component)
                    matched = true;
                if (URI::normalizeComponentName(subComponent) == nComp)
                    matched = true;
                if (subComponent == "*")
                    matched = true;
            }
            else {
                ;
            }
        }
        if (URI::getName(sub->getType()) == "Reply" && sub->getType() == mType) {
            // possible Reply<{hash}> subscription
            matched = true;
        }
        if (matched)
            if (!subs.contains(sub))
                subs.append(sub);
    }
    return subs;
}

void QueueBroker::routeMessage(IMessage* msg, QString sourceTransport) {
    qDebug() << "routeMessage" << msg->toString();

    // search subscribe by source component and message type
    QString mType = msg->getType();
    // sender:: sourceTransportName::sourceComponent
    QString sender = msg->getSender();
    QList<Subscribe *> foundedSubscriptions = searchSubscribes(sender, mType);
    qDebug() << "Found subscribes:" << foundedSubscriptions.length();
    QList<Subscribe *> removeList;
    if (foundedSubscriptions.count() > 0) {
        foreach (Subscribe *subscr, foundedSubscriptions) {

            qDebug() << "Matched subscription" << subscr->toString() << msg->toString();

            QList<ITransport *> dstTransports = getTransports(subscr->getDestinationTransport());

            if (dstTransports.length() > 0) {
                foreach (ITransport *trDest, dstTransports) {
                    if (trDest->isLocal()) {
                        QString dst = URI::getComponent(subscr->getDestination());
                        ILogic *dComp = getLogic(dst);
                        if (dComp) {
                            addTempSubscribe(*subscr, *msg);
                            dComp->receive(msg);
                        }
                    }
                    else {
                        addTempSubscribe(*subscr, *msg);
                        send(trDest, msg);
                    }
                }
                if (subscr->getType() == "Reply<" + msg->getHash() + ">") {
                    removeList.append(subscr);
                }
            }
            else {
                qDebug() << "No transports found, broken config?";
            }

        }
    }
    else {
        qDebug() << "No matched subcribes for message:" << msg->toString();
        if (msg->getType() == "Reply") {
            qDebug() << "Reply time-out?";
        }
    }
    foreach (Subscribe *sub, removeList) {
        if (m_subscribes.contains(sub))
            m_subscribes.removeOne(sub);
    }
}

void QueueBroker::send(ITransport *tr, IMessage *msg) {
    //if (!tr->isLocal()) {
    //    // append network address into message
    //    msg->setSender(tr->getName() + QString("::") + msg->getSender());
    //}
    QString compTarget = msg->getTarget();
    if (URI::getTransport(compTarget) == "Local<*>") {
        QStringList addrs = getRemoteComponentAddress(compTarget);
        if (addrs.length() > 0) {
            foreach (QString addr, addrs) {
                msg->setTarget(addr + "::" + compTarget);
                emit message(tr, msg);
            }
        }
        else {
            qDebug() << "Target unreachable" << compTarget;
        }
    }
    else {
        emit message(tr, msg);
    }
}

QList<ITransport *> QueueBroker::getTransports(QString trName) {
    QList<ITransport *> trs;
    if (
            ((trName.contains("<") && trName.contains(">")) && trName.contains("<*>"))
            || !(trName.contains("<") && trName.contains(">"))
        ){
        foreach (ITransport *tr, m_transports) {
            if (tr->getName().split("<")[0] == trName.split("<")[0])
                trs.append(tr);
        }
    }
    else {
        if (m_transports.contains(trName))
            trs.append(m_transports[trName]);
        else if (m_addr_map.contains(trName))
            trs.append(m_transports[m_addr_map[trName]]);
        else {
            ;
        }
    }
    return trs;
}

void QueueBroker::on_message(IMessage *message) {
    qDebug() << "receive(IMessage)" << message->toString();
    routeMessage(message, QString("Local"));
}

void QueueBroker::on_message(QString message) {
    // source - network transport remote address
    qDebug() << "receive(QString)" << message;
    IMessage *msg = new IMessage(message);
    ITransport *tr = static_cast<ITransport*>(sender());
    QString msgDstAddr = URI::getTransport(msg->getTarget());
    if (tr->isLocalAddress(URI::getTransportAddress(msgDstAddr))) {
        msg->setTarget(URI::getComponent(msg->getTarget()));
    }
    if (!m_addr_map.contains(URI::getTransport(msg->getSender())))
        m_addr_map[URI::getTransport(msg->getSender())] = tr->getName();
    routeMessage(msg, tr->getName());
}

void QueueBroker::addComponent(ILogic *component) {
    qDebug() << "Add logic component:" << component->getName() << "[" << m_components.size() << "]";
    m_components[URI::normalizeComponentName(component->getName())] = component;
    connect(component, SIGNAL(message(IMessage*)), SLOT(on_message(IMessage*)));
}

void QueueBroker::addComponent(ITransport *component) {
    qDebug() << "Add transport component:" << component->getName() << "[" << m_transports.size() << "]";
    if (!m_transports.contains(component->getName()))
        m_transports[component->getName()] = component;
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

void QueueBroker::removeComponent(ITransport *component) {

    m_transports.remove(URI::normalizeAddress(component->getName()));
}

void QueueBroker::removeComponent(ILogic *component) {

    m_components.remove(URI::normalizeComponentName(component->getName()));
}

void QueueBroker::registerRemoteComponent(QString cName, QString rAddress) {
    QString nComp = URI::normalizeComponentName(cName);
    if (!m_remoteComponents.contains(nComp)) {
        QList<QString> lst;
        lst << rAddress;
        m_remoteComponents[nComp] = lst;
    }
    else {
        if (!m_remoteComponents[nComp].contains(rAddress)) {
            QList<QString> lst;
            lst << rAddress;
            m_remoteComponents[nComp] = lst;
        }
    }
}

QStringList QueueBroker::getRemoteComponentAddress(QString cName) {
    QString nComp = URI::normalizeComponentName(cName);
    QStringList rAddrs;
    if (m_remoteComponents.contains(nComp)) {
        rAddrs = m_remoteComponents[nComp];
    }
    return rAddrs;
}

void QueueBroker::addSubscribe(QString &subscribe) {
    qDebug() << "addSubscribe()" << subscribe;

    Subscribe* sub = new Subscribe(subscribe);
    if (!m_subscribes.contains(sub)) {
        m_subscribes.append(sub);
    }

}
