#ifndef CLIENTSOCKETADAPTER_H
# define CLIENTSOCKETADAPTER_H

#include <QTcpSocket>
#include <QHostAddress>
# include "socketadapter.h"

class ClientSocketAdapter : public SocketAdapter {
    Q_OBJECT
public:
    explicit ClientSocketAdapter(QObject *parent);
    QString getAddress();
    inline QString getRemoteAddress() { return m_ptcpSocket->peerAddress().toString(); }
    inline int getPort() { return m_ptcpSocket->localPort(); }
    inline int getRemotePort() { return m_ptcpSocket->peerPort(); }
    bool isLocal();
    bool isConnected();

    void send(QString);
    bool connect(QString host, int port);
public slots:
    void disconnect();
private:
    bool m_connected = false;
signals:
    void connected();
};

#endif // CLIENTSOCKETADAPTER_H
