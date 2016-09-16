#ifndef SERVERSOCKETADAPTER_H
# define SERVERSOCKETADAPTER_H

# include "../common/transport/socketadapter.h"

class ServerSocketAdapter : public SocketAdapter {
    Q_OBJECT
public:
    explicit ServerSocketAdapter(QTcpSocket* pSock, QObject *parent = 0);
    QString getAddress();
};

#endif // SERVERSOCKETADAPTER_H
