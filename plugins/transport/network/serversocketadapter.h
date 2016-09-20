#ifndef SERVERSOCKETADAPTER_H
# define SERVERSOCKETADAPTER_H

#include <QTcpSocket>
#include <QHostAddress>
# include "socketadapter.h"

class ServerSocketAdapter : public SocketAdapter {
    Q_OBJECT
public:
    explicit ServerSocketAdapter(QTcpSocket* pSock, QObject *parent = 0);
    QString getAddress() { return m_ptcpSocket->peerAddress().toString(); }
    inline QString getLocalAddress() { return m_ptcpSocket->localAddress().toString(); }
    inline int getLocalPort() { return m_ptcpSocket->localPort(); }
    int getPort() { return m_ptcpSocket->peerPort(); }
};

#endif // SERVERSOCKETADAPTER_H
