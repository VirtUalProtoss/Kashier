#include "clientsocketadapter.h"
#include <QVector>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>


ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent) {
    // TODO: replace this to set params from config (ini file)
    m_ptcpSocket->connectToHost("10.19.205.244", 8765);
}

QString ClientSocketAdapter::getAddress() {
    //QString addr = m_ptcpSocket->peerAddress().toString();
    QString addr = m_ptcpSocket->localAddress().toString();
    return addr;
}

bool ClientSocketAdapter::isLocal() {
    return false;
}
