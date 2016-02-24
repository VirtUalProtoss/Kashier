#include "packet.h"

Packet::Packet(QObject *parent) : QObject(parent) {

}

QString Packet::toString() {
    return sourceTransport + ":" + sourceComponent + ";"
            + destinationTransport + ":" + destinationComponent + ";"
            + msg->toString();
}
