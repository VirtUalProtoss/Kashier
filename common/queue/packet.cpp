#include "packet.h"
#include <QStringList>

Packet::Packet(QObject *parent) : QObject(parent) {

}

QString Packet::toString() {
    return \
        sourceAddress + ":" + sourcePort + "$$" + \
        destinationAddress + ":" + destinationPort + "$$" + \
        QString(data.length()) + "$$" + \
        data + "$&";
}

void Packet::fromString(QString in_msg) {
    QStringList items = in_msg.split("$$");
    QString source = items[0];
    sourceAddress = source.split(":")[0];
    sourcePort = source.split(":")[1].toInt();
    QString destination = items[1];
    destinationAddress = destination.split(":")[0];
    destinationPort = destination.split(":")[1].toInt();
    int dLength = items[2].toInt();
    QString pdata = items[3].left(dLength);
    //pdata = pdata.left(dLength);
    data = pdata;
}

void Packet::setSourceAddress(QString addr)
{
    sourceAddress = addr.split(":")[0];
    sourcePort = addr.split(":")[1].toInt();
}

void Packet::setDestinationAddress(QString addr)
{
    destinationAddress = addr.split(":")[0];
    destinationPort = addr.split(":")[1].toInt();
}

void Packet::setData(QString pdata) {
    data = pdata;
}
