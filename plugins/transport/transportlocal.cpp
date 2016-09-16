#include "transportlocal.h"

TransportLocal::TransportLocal(QObject *parent) : ITransport(parent) {

}

QString TransportLocal::getName() {
    return QString("Local");
}

QString TransportLocal::getAddress() {
    return QString("");
}
