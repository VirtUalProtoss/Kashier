#include "itransport.h"

ITransport::ITransport(QObject *parent) : QObject(parent) {

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

void ITransport::send(QString data) {

}

void ITransport::setInitParams(QMap<QString, QVariant> *initParams) {
    _initParams = initParams;
    emit init_complete();
}

