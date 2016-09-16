#ifndef TRANSPORTNETWORK_H
#define TRANSPORTNETWORK_H

#include <QTcpServer>
#include <QTcpSocket>

#include "itransport.h"
#include "packet.h"

#include "serversocketadapter.h"
#include "clientsocketadapter.h"

class TransportNetwork : public ITransport {
public:
    explicit TransportNetwork(QObject *parent);
    QString getName();
    QString getAddress();

signals:

public slots:
    void on_newConnection();
    void on_disconnected();
    void on_message(QString msg);
    void on_message(Packet* msg);
private:
	ClientSocketAdapter* m_ptcpClient;
	QList<ISocketAdapter*> m_clients;
    QTcpServer* m_ptcpServer;
};

#endif // TRANSPORTNETWORK_H
