#include "iqueuebroker.h"
#include <QDebug>

IQueueBroker::IQueueBroker(QObject *parent) : QObject(parent) {

}

void IQueueBroker::send(IMessage *message) {
    qDebug() << "IQueueBroker::send(IMessage *message)" << message;
}

void IQueueBroker::receive(IMessage *message) {
    qDebug() << "IQueueBroker::receive(IMessage *message)" << message;
}

void IQueueBroker::receive(QString message) {

}

void IQueueBroker::startBroking() {

}

void IQueueBroker::addSubscribe(QString &subscribe) {

}

void IQueueBroker::addComponent(ILogic *component) {

}

void IQueueBroker::addComponent(ITransport *component) {

}

void IQueueBroker::removeComponent(ITransport *component) {

}

void IQueueBroker::removeComponent(ILogic *component) {

}

void IQueueBroker::publishComponents() {

}

void IQueueBroker::addComponentMap(ITransport *transport, ILogic *component) {

}

void IQueueBroker::addComponentMap(ITransport *transport, QString component) {

}

void IQueueBroker::registerRemoteSubscribe(QString key, QString sub) {

}
