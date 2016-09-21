#include "queuebroker.h"
#include <typeinfo>

#include "uri.h"

QueueBroker::QueueBroker(QObject *parent) : QObject(parent) {

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

void QueueBroker::removeSubscribes(QString dstTransportName) {
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
    return subs;
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
                                //processBrokerMessage(msg, srcTransport);
                                ;
                            }
                        }
                        else {
                            ILogic *dComp = getLogic(dstComponentName);
                            if (dComp)
                                dComp->receive(msg);
                        }
                    }
                    else {
                        emit message(trDest, msg);
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
        foreach (ITransport *tr, m_transports) {
            if (tr->getName().split("<")[0] == trName.split("<")[0])
                trs.append(tr);
        }
    }
    else {
        if (m_transports.contains(trName))
            trs.append(m_transports[trName]);
    }
    return trs;
}

void QueueBroker::on_message(QString message, QString source) {
    IMessage *msg = new IMessage(message);
    ITransport *tr = static_cast<ITransport*>(sender());
    routeMessage(msg, tr->getName());
}

void QueueBroker::addComponent(ILogic *component) {
    qDebug() << "Add logic component:" << component->getName() << "[" << m_components.size() << "]";
    m_components[URI::normalizeComponentName(component->getName())] = component;
    connect(component, SIGNAL(message(IMessage*)), SLOT(receive(IMessage*)));
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

void QueueBroker::addSubscribe(QString &subscribe) {
    qDebug() << "addSubscribe()" << subscribe;

    Subscribe* sub = new Subscribe(subscribe);
    if (m_subscribes.contains(sub)) {
        ;
    }

}
