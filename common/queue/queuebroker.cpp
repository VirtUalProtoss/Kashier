#include "queuebroker.h"

#include <typeinfo>

#include "uri.h"
#include "reply.h"

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
            params[logic->getName()] = logic->getName();
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

QList<Subscribe *> QueueBroker::searchSubscribes(Subscribe *msgSub) {
    QList<Subscribe *> subs;

    QString msgSubHash = msgSub->getHash();
    if (m_sub_hashes.contains(msgSubHash)) {
        // Точное совпадение по хэшу
        subs.append(m_sub_hashes[msgSubHash]);
    }

    // Медленный поиск по широковещательным подпискам
    QString msgSource = msgSub->getSource().toString();
    bool matchType = false;
    bool matchSrc = false;
    QList<Subscribe *> removeList;
    foreach (Subscribe* sub, m_subscribes) {
        if (sub->isTimeout()) {
            removeList.append(sub);
            continue;
        }

        matchType = false;
        matchSrc = false;

        QString subSource = sub->getSource().toString();

        if (sub->getType() == "*" || sub->getType() == msgSub->getType())
            matchType = true;

        if (sub->addrMatch(subSource, msgSource))
            matchSrc = true;

        if (matchType && matchSrc)
            if (!subs.contains(sub))
                subs.append(sub);
    }

    // Удаление просроченных подписок
    foreach (Subscribe *sub, removeList) {
        if (m_subscribes.contains(sub))
            m_subscribes.removeOne(sub);
        if (m_sub_hashes.contains(sub->getHash()))
            m_sub_hashes.remove(sub->getHash());
    }
    return subs;
}

void QueueBroker::routeMessage(IMessage* msg, ITransport* sourceTransport) {
    qDebug() << "routeMessage" << msg->toString();

    /*
    QString mType = msg->getType();
    bool needResponce = false;
    Subscribe *msgSub;
    if (mType == "Query") {
        Query *tMsg = new Query(msg);
        needResponce = tMsg->needResponce();
        msgSub = new Subscribe(tMsg->getSubscribe());
    }
    else if (mType == "Reply") {
        Query *tQuery = new Query(msg);
        Reply *tMsg = new Reply(tQuery);
        needResponce = tMsg->needResponce();
        msgSub = new Subscribe(tMsg->getSubscribe());
    }
    else {
        IMessage *tMsg = msg;
        needResponce = tMsg->needResponce();
        msgSub = new Subscribe(tMsg->getSubscribe());
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

    Subscribe *msgSub = new Subscribe(msg->getSubscribe());
    bool needResponce = msg->needResponce();

    QList<Subscribe *> foundedSubscriptions = searchSubscribes(msgSub);
    qDebug() << "Found subscribes:" << foundedSubscriptions.length();

    if (foundedSubscriptions.count() > 0) {
        QList<Subscribe *> removeList;
        foreach (Subscribe *subscr, foundedSubscriptions) {

            qDebug() << "Matched subscription" << subscr->toString() << msg->toString();

            QList<ITransport *> dstTransports = getTransports(subscr->getDestination().getTransport());

            if (dstTransports.length() > 0) {
                foreach (ITransport *trDest, dstTransports) {

                    if (needResponce)
                        addSubscribe(msgSub);

                    if (trDest->isLocal()) {
                        ILogic *dComp = getLogic(subscr->getDestination().getComponent());
                        if (dComp)
                            dComp->receive(msg);
                        else
                            qDebug() << "No logic component found for" << subscr->getDestination().getComponent();
                    }
                    else {
                        msg->setTarget(subscr->getDestination());
                        send(trDest, msg);
                    }
                }
            }
            else {
                qDebug() << "No transports found, remove subscribe from list";
                removeList.append(subscr);
            }

        }
        // Удаление просроченных подписок
        foreach (Subscribe *sub, removeList) {
            if (m_subscribes.contains(sub))
                m_subscribes.removeOne(sub);
            if (m_sub_hashes.contains(sub->getHash()))
                m_sub_hashes.remove(sub->getHash());
        }
    }
    else {
        qDebug() << "No matched subcribes for message:" << msg->toString();
        if (msg->getType() == "Reply") {
            qDebug() << "Reply time-out?";
        }
        else {
            qDebug() << "Need add broadcast subscribe for:" << msg->getSubscribe();
        }
    }
}

void QueueBroker::send(ITransport *tr, IMessage *msg) {
    emit message(tr, msg);
}

QList<ITransport *> QueueBroker::getTransports(QString trName) {
    QList<ITransport *> trs;
    QString nTrName = URI::normalizeComponentName(trName);
    if (nTrName.contains("<*>")) {
        foreach (QString key, m_transports.keys()) {
            trs.append(m_transports[key]);
        }
    }
    else {
        if (m_transports.contains(trName))
            trs.append(m_transports[trName]);
    }

    if (m_addr_map.contains(trName))
        trs.append(m_addr_map[trName]);

    if (m_remoteComponents.contains(nTrName))
        foreach (QString key, m_remoteComponents[nTrName]) {
            QString addr = URI::getComponentParams(key);
            if (m_addr_map.contains(addr))
                trs.append(m_addr_map[addr]);
        }

    if (m_remoteComponents.contains(trName))
        foreach (QString key, m_remoteComponents[trName]) {
            QString addr = URI::getComponentParams(key);
            if (m_addr_map.contains(addr))
                trs.append(m_addr_map[addr]);
        }

    return trs;
}

void QueueBroker::on_message(IMessage *message) {
    qDebug() << "Receive local message(IMessage):" << message->toString();
    routeMessage(message, getTransport(QString("Local<*>")));
}

void QueueBroker::on_message(QString message) {
    // source - network transport remote address
    qDebug() << "Receive network message(QString):" << message;
    IMessage *msg = new IMessage(message);


    ITransport *tr = static_cast<ITransport*>(sender());

    QString msgDstAddr = msg->getTarget().getAddress();
    // сообщение для нас
    if (tr->isLocalAddress(msgDstAddr)) {
        // Снимаем транспортный адрес назначения с сообщения
        //msg->setTarget(msg->getTarget());

        // Добавляем мап адрес-транспорт из сообщения
        QString msgSrcAddr = msg->getSender().getAddress();
        if (!m_addr_map.contains(msgSrcAddr))
            m_addr_map[msgSrcAddr] = tr;

        routeMessage(msg, tr);
    }
    else {
        qDebug() << "Drop alien message" << msg->toString();
    }
}

void QueueBroker::addComponent(ILogic *component) {
    QString cName = component->getName();
    qDebug() << "Add logic component:" << cName << "[" << m_components.size() << "]";
    m_components[cName] = component;
    connect(component, SIGNAL(message(IMessage*)), SLOT(on_message(IMessage*)));
}

void QueueBroker::addComponent(ITransport *component) {
    QString cName = component->getName();
    qDebug() << "Add transport component:" << cName << "[" << m_transports.size() << "]";
    if (!m_transports.contains(cName))
        m_transports[cName] = component;
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
    m_transports.remove(component->getName());
}

void QueueBroker::removeComponent(ILogic *component) {
    m_components.remove(component->getName());
}

void QueueBroker::registerRemoteComponent(QString cName, QString rAddress) {
    if (!m_remoteComponents.contains(cName)) {
        QList<QString> lst;
        lst << rAddress;
        m_remoteComponents[cName] = lst;
    }
    else {
        if (!m_remoteComponents[cName].contains(rAddress)) {
            QList<QString> lst;
            lst << rAddress;
            m_remoteComponents[cName] = lst;
        }
    }
}

void QueueBroker::addSubscribe(QString &subscribe) {
    qDebug() << "addSubscribe(QString)" << subscribe;

    Subscribe* sub = new Subscribe(subscribe);
    addSubscribe(sub);
}

void QueueBroker::addSubscribe(Subscribe *subscribe) {
    qDebug() << "addSubscribe(Subscribe)" << subscribe->toString();
    if (!m_subscribes.contains(subscribe)) {
        m_subscribes.append(subscribe);
    }

    if (!m_sub_hashes.contains(subscribe->getHash())) {
        m_sub_hashes.insert(subscribe->getHash(), subscribe);
    }
}
