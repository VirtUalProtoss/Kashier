#include "ilogic.h"
#include <QDebug>
#include "queuebroker.h"

ILogic::ILogic(QObject *parent) : QObject(parent) {
    m_broker = static_cast<QueueBroker*>(parent);
}

void ILogic::setInitParams(QMap<QString, QVariant> *initParams) {
    _initParams = initParams;
    emit init_complete();
}

QString ILogic::getName() {
    return name;
}

void ILogic::setName(QString name) {
    name = name;
}

bool ILogic::isPublic() {
    if (name != "Local")
        return true;
    else
        return false;
}

void ILogic::receive(IMessage *msg) {
    qDebug() << "ILogic" << getName() << "receive message" << msg->toString();
}

void ILogic::emit_message(IMessage *msg) {
    emit message(msg);
}

void ILogic::subscribe(QString sub) {
    m_broker->addSubscribe(sub);
}

