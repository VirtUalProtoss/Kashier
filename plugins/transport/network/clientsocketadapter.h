#ifndef CLIENTSOCKETADAPTER_H
# define CLIENTSOCKETADAPTER_H

# include "socketadapter.h"

class ClientSocketAdapter : public SocketAdapter {
    Q_OBJECT
public:
    explicit ClientSocketAdapter(QObject *parent);
    QString getAddress();
    bool isLocal();
    bool isConnected();

    void send(QString);
    bool connect(QString host, int port);
public slots:
    void disconnect();
private:
    bool connected = false;
};

#endif // CLIENTSOCKETADAPTER_H
