#include "clientsocketadapter.h"
#include <QVector>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>


ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent) {
    // TODO: replace this to set params from config (ini file)
    m_ptcpSocket->connectToHost("127.0.0.1", 8765);
}

QString ClientSocketAdapter::getAddress() {
    //QString addr = m_ptcpSocket->peerAddress().toString();
    QString addr = m_ptcpSocket->localAddress().toString();
    return addr;
}

bool ClientSocketAdapter::isLocal() {
    return false;
}
