#include "clientsocketadapter.h"
#include <QVector>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>


ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent) {
    // TODO: replace this to set params from config (ini file)
    m_ptcpSocket->connectToHost("192.168.0.11", 8765);
    if (m_ptcpSocket->waitForConnected(1000)) {
         connected = true;
         setName(QString("Network<" + getAddress() + QString(">")));
    }
}

QString ClientSocketAdapter::getAddress() {
    //QString addr = m_ptcpSocket->peerAddress().toString();
    QString addr = m_ptcpSocket->localAddress().toString();
    return addr;
}

bool ClientSocketAdapter::isLocal() {
    return false;
}

bool ClientSocketAdapter::isConnected() {
    return connected;
}

QString ClientSocketAdapter::getName() {
    return name;
    //return QString("Network<") + getAddress() + QString(">");
}

void ClientSocketAdapter::send(QString data) {
    sendString(data);
}

void ClientSocketAdapter::disconnect() {
    connected = false;
}
