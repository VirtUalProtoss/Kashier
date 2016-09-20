#include "serversocketadapter.h"

ServerSocketAdapter::ServerSocketAdapter(QTcpSocket* pSock, QObject *parent) : SocketAdapter(parent, pSock) {
    m_ptcpSocket->IPv4Protocol;
}
