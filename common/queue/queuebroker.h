#ifndef QUEUEBROKER_H
#define QUEUEBROKER_H

#include <QDebug>

#include "iqueuebroker.h"
#include "imessage.h"
#include "query.h"
#include "packet.h"
#include "messagebuilder.h"
#include "subscribe.h"


class QueueBroker : public IQueueBroker {

public:
    QueueBroker(QObject *parent);
    void putMessage(IMessage* message);
    //void send(IMessage* message);
    //void receive(IMessage* message);

    void startBroking();
    void addSubscribe(QString &subscribe);
    void addComponent(ILogic* component);
    void addComponent(ITransport* component);
    void addComponentMap(ITransport* transport, ILogic* component);
    void addComponentMap(ITransport *transport, QString component);
    void removeComponent(ITransport* component);
    void removeComponent(ILogic* component);

    void publishComponents();
    void routePacket(Packet *packet);
    QString getMapName(ITransport *transport, ILogic *component);
    void registerRemoteSubscribe(QString key, QString sub);
private:
    QList<IMessage*> queue;
    //   source        message  destination
    QMap<QString, QMap<QString, QList<QString>>> subscribes;
    QMap<QString, QMap<QString, QList<QString>>> tempSubscribes;

    QMap<ILogic*, QString> components;
    QMap<ITransport*, QString> transports;

    QMap<QString, ILogic*> componentMap;
    QMap<QString, ITransport*> remoteComponents;

    QMap<ITransport*, ILogic*> getComponentMap(QString &pair);
    void subscribe(
            ITransport& sourceTransport,
            ILogic& sourceComponent,
            IMessage& messageType,
            ITransport& destinationTransport,
            ILogic& destinationComponent);
    ITransport* getTransport(QString &transport);
    ILogic* getLogic(QString &logic);
    IMessage* getMessage(QString &messageType);

    void registerRemoteComponents(IMessage *msg, QString srcTransport);
public slots:
    void send(IMessage *message);
    void receive(IMessage *message);
    void receive(QString message);
protected:
    void routeMessage(IMessage *msg, QString srcTransport);
    bool matchMap(QString src, QString dest);
};

#endif // QUEUEBROKER_H
