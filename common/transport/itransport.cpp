#include "itransport.h"

ITransport::ITransport(QObject *parent) : QObject(parent) {

}

QString ITransport::getAddress() {
    return QString("ITransportAddress");
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

