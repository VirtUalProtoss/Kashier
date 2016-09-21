#include "clientsocketadapter.h"
#include <QVector>
#include <QDataStream>


ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent) {

}

QString ClientSocketAdapter::getAddress() {
    return m_ptcpSocket->localAddress().toString();
}

bool ClientSocketAdapter::connect(QString host, int port) {
    m_connected = false;
    m_ptcpSocket->connectToHost(host, port);
    if (m_ptcpSocket->waitForConnected(1000)) {
         m_connected = true;
         setName(QString("Network<" + getAddress() + QString(">")));
    }
    emit connected();
    return m_connected;
}

bool ClientSocketAdapter::isLocal() {
    return false;
}

bool ClientSocketAdapter::isConnected() {
    return m_connected;
}



void ClientSocketAdapter::send(QString data) {
    sendString(data);
}

void ClientSocketAdapter::disconnect() {
    m_connected = false;
}
