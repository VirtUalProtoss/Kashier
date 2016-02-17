#include "queuebroker.h"

QueueBroker::QueueBroker(QObject *parent) : IQueueBroker(parent) {

}

void QueueBroker::putMessage(IMessage *message) {
    queue.append(message);
}

void QueueBroker::send(IMessage *message) {

}

void QueueBroker::receive(IMessage *message) {

}

void QueueBroker::subscribe(
        ITransport *sourceTransport,
        ILogic *sourceComponent,
        IMessage *messageType,
        ITransport *destinationTransport,
        ILogic *destinationComponent)
{

}

