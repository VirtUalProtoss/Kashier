#include "serversocketadapter.h"
#include <QTcpSocket>
#include <QHostAddress>


ServerSocketAdapter::ServerSocketAdapter(QTcpSocket* pSock, QObject *parent) :
    SocketAdapter(parent, pSock) {
}

QString ServerSocketAdapter::getAddress() {
    return m_ptcpSocket->peerAddress().toString();
}
