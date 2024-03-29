#ifndef TRANSPORTNETWORK_H
#define TRANSPORTNETWORK_H

#include <QObject>
#include <QTcpServer>

#include "itransport.h"
#include "packet.h"

#include "socketadapter.h"

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
    QString getRemoteAddress();
    inline bool isLocal() { return false; }
    bool isLocalAddress(QString address);

    void changeMode(QString mode, QMap<QString, QVariant> params);
signals:
    void message(QString);
public slots:
    void on_newConnection();
    void on_disconnected();
    void on_client_connected();
    void on_network_message(QString msg);
    void disconnect();
    void on_init_complete();
    void on_broker_message(ITransport*, IMessage*);
private:
    SocketAdapter* m_ptcpClient;
    QMap<QString, SocketAdapter*> m_clients;
    QTcpServer* m_ptcpServer;
    QString m_mode;

    void sendSockMessage(SocketAdapter *sock, IMessage *msg);
};

#endif // TRANSPORTNETWORK_H
