#include "serversocketadapter.h"

ServerSocketAdapter::ServerSocketAdapter(QTcpSocket* pSock, QObject *parent) : SocketAdapter(parent, pSock) {
    m_ptcpSocket->IPv4Protocol;
}

void ServerSocketAdapter::on_message(ITransport *tr, IMessage *msg) {
    emit message(tr, msg);
}
