#include "iqueuebroker.h"
#include <QDebug>

IQueueBroker::IQueueBroker(QObject *parent) : QObject(parent) {

}

void IQueueBroker::send(IMessage *message) {

}

void IQueueBroker::receive(IMessage *message) {

}

void IQueueBroker::subscribe(
        ITransport *sourceTransport,
        ILogic *sourceComponent,
        IMessage *messageType,
        ITransport *destinationTransport,
        ILogic *destinationComponent)
{
    qDebug() << "virtual subscribe()" << endl;
}
