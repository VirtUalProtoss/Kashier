#ifndef CLIENTSOCKETADAPTER_H
# define CLIENTSOCKETADAPTER_H

# include "../common/transport/socketadapter.h"

class ClientSocketAdapter : public SocketAdapter {
    Q_OBJECT
public:
    explicit ClientSocketAdapter(QObject *parent);
    QString getAddress();
    bool isLocal();
    bool isConnected();
    QString getName();
    void send(QString);
public slots:
    void disconnect();
private:
    bool connected = false;
};

#endif // CLIENTSOCKETADAPTER_H
