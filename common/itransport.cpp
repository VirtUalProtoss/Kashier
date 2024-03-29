#include "itransport.h"
#include "queuebroker.h"


ITransport::ITransport(QObject *parent) : QObject(parent) {
    m_broker = static_cast<QueueBroker*>(parent);
}

QString ITransport::getAddress() {
    return QString("ITransportAddress");
}

QString ITransport::getRemoteAddress() {
    return QString("ITransportRemoteAddress");
}

QString ITransport::getName() {
    return name;
}

void ITransport::setName(QString tName) {
    name = tName;
}

bool ITransport::isLocal() {
    return true;
}

bool ITransport::isLocalAddress(QString address) {
    qDebug() << "ITransport::isLocalAddress(QString address):" << address;
    return false;
}

void ITransport::send(QString data) {
    qDebug() << "ITransport::send(QString data):" << data;
}

void ITransport::setInitParams(QMap<QString, QVariant> *initParams) {
    _initParams = initParams;
    emit init_complete();
}

