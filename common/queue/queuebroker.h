#ifndef QUEUEBROKER_H
#define QUEUEBROKER_H

#include <QDebug>

#include "iqueuebroker.h"
#include "imessage.h"
#include "query.h"
#include "packet.h"
#include "messagebuilder.h"


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
    void removeComponent(ITransport* component);
    void removeComponent(ILogic* component);

    void publishComponents();
private:
    QList<IMessage*> queue;
    QList<QObject*> subscribes;
    QMap<ILogic*, QString> components;
    QMap<ITransport*, QString> transports;
    //QMap<ITransport*, ILogic*> componentMap;
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

public slots:
    void send(IMessage *message);
    void receive(IMessage *message);
    void receive(QString message);
};

#endif // QUEUEBROKER_H
