#ifndef TRANSPORTNETWORK_H
#define TRANSPORTNETWORK_H

//#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "itransport.h"
#include "packet.h"

#include "serversocketadapter.h"
#include "clientsocketadapter.h"

#include "plugininterface.h"
#include "queuebroker.h"

class TransportNetwork : public ITransport, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Kashier.Transport.Network")
    Q_INTERFACES(PluginInterface)
public:
    explicit TransportNetwork(QObject *parent = 0);
    QString getName();
    QString getAddress();

signals:

public slots:
    void on_newConnection();
    void on_disconnected();
    void on_message(QString msg);
    void on_message(Packet* msg);
    void disconnect();
private:
    QueueBroker* m_broker;
	ClientSocketAdapter* m_ptcpClient;
	QList<ISocketAdapter*> m_clients;
    QTcpServer* m_ptcpServer;
};

#endif // TRANSPORTNETWORK_H
