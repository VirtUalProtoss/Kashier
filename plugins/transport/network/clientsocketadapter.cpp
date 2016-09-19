#include "clientsocketadapter.h"
#include <QVector>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>


ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent) {

}

QString ClientSocketAdapter::getAddress() {
    QString addr = m_ptcpSocket->localAddress().toString() + ":" + QString(m_ptcpSocket->localPort());
    return addr;
}

bool ClientSocketAdapter::connect(QString host, int port) {
    bool connected = false;
    m_ptcpSocket->connectToHost(host, port);
    if (m_ptcpSocket->waitForConnected(1000)) {
         connected = true;
         setName(QString("Network<" + getAddress() + QString(">")));
    }
    return connected;
}

bool ClientSocketAdapter::isLocal() {
    return false;
}

bool ClientSocketAdapter::isConnected() {
    return connected;
}



void ClientSocketAdapter::send(QString data) {
    sendString(data);
}

void ClientSocketAdapter::disconnect() {
    connected = false;
}
