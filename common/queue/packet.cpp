#include "packet.h"

Packet::Packet(QObject *parent) : QObject(parent) {

}

QString Packet::toString() {
    return sourceTransport + ":" + sourceComponent + ";"
            + destinationTransport + ":" + destinationComponent + ";"
            + msg->toString();
}



void Packet::fromString(QString in_msg) {
    QStringList items = in_msg.split(";");
    IMessage* m_msg = new IMessage(this);
    if (items.length() > 2) {
        QString source = items[0];
        sourceTransport = source.split(":")[0];
        sourceComponent = source.split(":")[1];
        QString destination = items[1];
        destinationTransport = destination.split(":")[0];
        destinationComponent = destination.split(":")[1];
        m_msg->fromString(items[2]);
    }
    else {
        m_msg->fromString(in_msg);
    }
    msg = m_msg;
}
