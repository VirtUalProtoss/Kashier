#ifndef QUEUEBROKER_H
#define QUEUEBROKER_H

#include "iqueuebroker.h"
#include "imessage.h"
#include "query.h"


class QueueBroker : public IQueueBroker {
public:
    QueueBroker(QObject *parent);
    void putMessage(IMessage* message);
    void send(IMessage* message);
    void receive(IMessage* message);
    void subscribe(
            ITransport* sourceTransport,
            ILogic* sourceComponent,
            IMessage* messageType,
            ITransport* destinationTransport,
            ILogic* destinationComponent);
private:
    QList<IMessage*> queue;
};

#endif // QUEUEBROKER_H
