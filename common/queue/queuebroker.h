#ifndef QUEUEBROKER_H
#define QUEUEBROKER_H

#include <QDebug>
#include <QObject>

#include "imessage.h"
#include "query.h"
#include "messagebuilder.h"
#include "subscribe.h"

#include "ilogic.h"
#include "itransport.h"
#include "plugininterface.h"
#include "subscribe.h"
#include "logicqueuebroker.h"


class QueueBroker : public QObject {
    Q_OBJECT
public:
    explicit QueueBroker(QObject *parent);
    void addSubscribe(QString &subscribe);
    void addSubscribe(Subscribe *subscribe);
    void addComponent(ILogic* component);
    void addComponent(ITransport* component);
    void addComponent(PluginInterface* component, QMap<QString, QVariant> params);
    void removeComponent(ITransport* component);
    void removeComponent(ILogic* component);
    void registerRemoteComponent(QString cName, QString rAddress);

    void publishComponents(QString transport = QString("Network"), QString target = QString("Broker<*>"));
    void searchSubscribes(Subscribe *msgSub, QList<Subscribe *> *subs);
    QList<ITransport *> getTransports(QString trName);
    void removeSubscribes(QString dstTransportName);
private:
    QList<Subscribe*> m_subscribes;
    QHash<QString, Subscribe*> m_sub_hashes;

    QMap<QString, ILogic*>      m_components;
    QMap<QString, ITransport*>  m_transports;

    ITransport* getTransport(QString transport);
    ILogic* getLogic(QString logic);

    void routeMessage(IMessage *msg);
    bool matchMap(QString src, QString dest);
    QMap<QString, QList<QString>> m_remoteComponents;
    QMap<QString, ITransport*> m_addr_map;

    void send(ITransport *tr, IMessage *msg);
    void populateSubscribeInstances(QList<Subscribe *> popSubs);
public slots:
    // local components messages
    void on_message(IMessage*);
    // transports messages, source = in-transport sender
    void on_message(QString message);
signals:
    // signal to transport for send message
    void message(ITransport*, IMessage*);
};

#endif // QUEUEBROKER_H
