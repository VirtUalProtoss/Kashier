#include "logicqueuebroker.h"
#include "imessage.h"

#include <QDebug>

LogicQueueBroker::LogicQueueBroker(QObject *parent) : ILogic(parent) {

}

void LogicQueueBroker::receive(IMessage *msg) {
    qDebug() << "Broker receive message" << msg->toString();
}
