#include "iqueuebroker.h"
#include <QDebug>

IQueueBroker::IQueueBroker(QObject *parent) : QObject(parent) {

}

void IQueueBroker::send(IMessage *message) {
    qDebug() << message;
}

void IQueueBroker::receive(IMessage *message) {
    qDebug() << message;
}

void IQueueBroker::startBroking() {

}

void IQueueBroker::addSubscribe(QString &subscribe)
{

}

void IQueueBroker::addComponent(ILogic *component)
{

}

void IQueueBroker::addComponent(ITransport *component)
{

}

void IQueueBroker::addComponentMap(ITransport *transport, ILogic *component)
{

}
