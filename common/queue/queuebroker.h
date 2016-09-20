#ifndef QUEUEBROKER_H
#define QUEUEBROKER_H

#include <QDebug>
#include <QObject>

#include "imessage.h"
#include "query.h"
#include "packet.h"
#include "messagebuilder.h"
#include "subscribe.h"

#include "ilogic.h"
#include "itransport.h"
#include "plugininterface.h"
#include "subscribe.h"

//class ILogic;
//class ITransport;


class QueueBroker : public QObject {
    Q_OBJECT
public:
    explicit QueueBroker(QObject *parent);
    void putMessage(IMessage* message);
    void startBroking();
    void addSubscribe(QString &subscribe);
    void addComponent(ILogic* component);
    void addComponent(ITransport* component);
    void addComponent(PluginInterface* component, QMap<QString, QVariant> params);
    void addComponentMap(ITransport* transport, ILogic* component);
    void addComponentMap(ITransport *transport, QString component);
    void removeComponent(ITransport* component);
    void removeComponent(ILogic* component);

    void publishComponents(QString transport = QString("Network"), QString target = QString("Broker<*>"));
    QList<Subscribe *> searchSubscribes(QString source, QString mType);
    void routePacket(Packet *packet);
    QString getMapName(ITransport *transport, ILogic *component);
    QList<ITransport *> getTransports(QString trName);
    void processBrokerMessage(IMessage *msg, ITransport *srcTransport);
    void removeSubscriptions(QString dstTransportName);
private:
    QList<IMessage*> queue;
    //   source   message_type  subscription list
    QMap<QString, QMap<QString, QMap<QString, Subscribe*>>> subscribes;
    QMap<QString, QMap<QString, QList<Subscribe*>>> tempSubscribes;

    QMap<QString, ILogic*> components;
    QMap<QString, ITransport*> transports;

    QMap<QString, ILogic*> componentMap;
    QMap<QString, ITransport*> remoteComponents;

    ITransport* getTransport(QString &transport);
    ILogic* getLogic(QString &logic);

    void registerRemoteComponents(IMessage *msg, QString srcTransport);
    void routeMessage(IMessage *msg, QString srcTransport);
    bool matchMap(QString src, QString dest);

public slots:
    void send(IMessage *message);
    void receive(IMessage *message);
    void receive(Packet *pkt, QString source);
    void receive(QString message);
signals:
    //void network_message(QString);
    void message(Packet*);
    void message(ITransport*, IMessage*);
};

#endif // QUEUEBROKER_H
