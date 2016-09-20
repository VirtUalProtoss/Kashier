#include "clientsocketadapter.h"
#include <QVector>
#include <QDataStream>


ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent) {

}

QString ClientSocketAdapter::getAddress() {
    return m_ptcpSocket->localAddress().toString();
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
