#include "transportnetwork.h"

TransportNetwork::TransportNetwork(QObject *parent) : ITransport(parent) {
    connect(this, SIGNAL(init_complete()), this, SLOT(on_init_complete()));
}

void TransportNetwork::changeMode(QString mode, QMap<QString, QVariant> params) {
    m_mode = mode;
    if (mode=="server") {
        m_ptcpServer = new QTcpServer(this);
        connect(m_ptcpServer, SIGNAL(newConnection()), SLOT(on_newConnection()));
        if (params.contains("address")){
            QString addr = params["address"].toString();
            int port = 8765;
            if (params.contains("port")) port = params["port"].toInt();
            if (false == m_ptcpServer->listen(QHostAddress(addr), port)) {
                m_ptcpServer->close();
                throw m_ptcpServer->errorString();
            }
        }

    }
    if (mode=="client") {
        m_ptcpClient = new SocketAdapter(this);

        connect(m_broker, 		SIGNAL(message(ITransport*, IMessage*)),    m_ptcpClient,  SLOT(on_message(ITransport *, IMessage *)));
        connect(m_ptcpClient,	SIGNAL(sock_message(ITransport*, IMessage*)),    SLOT(on_broker_message(ITransport *, IMessage *)));
        connect(m_ptcpClient, 	SIGNAL(disconnected()), 					SLOT(disconnect()));
        connect(m_ptcpClient, 	SIGNAL(connected()), 					SLOT(on_client_connected()));
        connect(this,        	SIGNAL(message(QString)), 	m_broker, 		SLOT(on_message(QString)));
        connect(m_ptcpClient, 	SIGNAL(message(QString)), 					SLOT(on_network_message(QString)));

        if (params.contains("address")){
            QString addr = params["address"].toString();
            int port = 8765;
            if (params.contains("port")) port = params["port"].toInt();
            m_ptcpClient->sock_connect(addr, port);
        }
        else {
            qDebug() << "No connection data specified";
        }

        //m_broker->publishComponents();
    }
    if (mode=="proxy") {
        ;
    }
}

QString TransportNetwork::getName() {
    QString port = QString("0");
    return QString("Network<") + m_mode + ":" + port + QString(">");
}

QString TransportNetwork::getAddress() {
    if (m_mode == "server") {
        return m_ptcpServer->serverAddress().toString();
    }
    else if (m_mode == "client") {
        return m_ptcpClient->getAddress();
    }
    else {
        return QString("127.0.0.1");
    }
}

QString TransportNetwork::getRemoteAddress() {
    if (m_mode == "server") {
        return QString("0.0.0.0");
    }
    else if (m_mode == "client") {
        return m_ptcpClient->getAddress();
    }
    else {
        return QString("127.0.0.1");
    }
}

void TransportNetwork::on_newConnection() {
    QTcpSocket* pclientSock = m_ptcpServer->nextPendingConnection();
    SocketAdapter *pSockHandle = new SocketAdapter(this, pclientSock);


    QString fullAddr = pSockHandle->getRemoteAddress() + ":" + QString::number(pSockHandle->getRemotePort());
    QTextStream(stdout) << "New connection from " << fullAddr << endl;
    pSockHandle->setName(QString("Broker<") + fullAddr + QString(">"));
    m_clients[pSockHandle->getName()] = pSockHandle;

    connect(m_broker, 		SIGNAL(message(ITransport*, IMessage*)),    pSockHandle,  SLOT(on_message(ITransport *, IMessage *)));
    connect(pSockHandle,	SIGNAL(sock_message(ITransport*, IMessage*)),    SLOT(on_broker_message(ITransport *, IMessage *)));
    connect(pSockHandle, 	SIGNAL(disconnected()), 					SLOT(on_disconnected()));
    connect(this,        	SIGNAL(message(QString)), 	m_broker, 		SLOT(on_message(QString)));
    connect(pSockHandle, 	SIGNAL(message(QString)), 					SLOT(on_network_message(QString)));

    QStringList subscribes;
    subscribes << getName() + QString("::") + pSockHandle->getName() + QString(";Broker;Message;Persist");
    foreach (QString subscribe, subscribes)
        m_broker->addSubscribe(subscribe);
    m_broker->publishComponents(getName(), pSockHandle->getName());
}

void TransportNetwork::on_disconnected() {
    SocketAdapter* pSock = static_cast<SocketAdapter*>(sender());
    QTextStream(stdout) << "Socket disconnected: " << pSock->getName() << endl;
    m_clients.remove(pSock->getName());
    m_broker->removeSubscribes(pSock->getName());
    delete pSock;
}

void TransportNetwork::on_client_connected() {
    SocketAdapter* client = static_cast<SocketAdapter*>(sender());
    QString fullAddr = client->getRemoteAddress() + ":" + QString::number(client->getRemotePort());
    client->setName(QString("Broker<") + fullAddr + QString(">"));

    qDebug() << "Connect to server:" << client->getRemoteAddress() + ":" + QString::number(client->getRemotePort()) << client->isConnected();
    m_broker->addComponent(this);

    QStringList subscribes;
    subscribes << getName() + QString("::") + client->getName() + QString(";Broker;Message;Persist");
    foreach (QString subscribe, subscribes)
        m_broker->addSubscribe(subscribe);
    m_broker->publishComponents(getName(), client->getName());
}

void TransportNetwork::on_network_message(QString msg) {
    // пришло сетевое сообщение
    SocketAdapter *source = (SocketAdapter*)sender();
    qDebug() << "Network message" << msg << "from" << source->getName();
    Packet* pkt = new Packet();
    pkt->fromString(msg);
    QString data = pkt->getData();
    emit message(data);
}

void TransportNetwork::disconnect() {
    // TODO: unregister remote transports, components, subscribes, notify local components
    SocketAdapter* client = static_cast<SocketAdapter*>(sender());
    QTextStream(stdout) << "Client disconnected" << client->getName() << endl;
}

void TransportNetwork::on_init_complete() {
    m_broker = static_cast<QueueBroker*>(this->parent());
    QString mode = "server";
    if (_initParams->contains("mode"))
        mode = _initParams->value("mode").toString();
    changeMode(mode, *_initParams);
}

void TransportNetwork::sendPacket(SocketAdapter *sock, Packet *pkt) {
    if (sock->isConnected()) {
        qDebug() << "Send message" << pkt->getData() << "to" << sock->getName();
        pkt->setDestinationAddress(sock->getRemoteAddress(), sock->getRemotePort());
        pkt->setSourceAddress(sock->getLocalAddress(), sock->getLocalPort());
        sock->sendString(pkt->toString());
    }
    else {
        qDebug() << "Socket" << sock->getName() << "disconnected";
    }
}

void TransportNetwork::on_broker_message(ITransport *tr, IMessage *msg) {
    // message from broker
    SocketAdapter *isock = static_cast<SocketAdapter*>(sender());
    if (tr==this) {
        QString target = msg->getTarget().split("::")[0];
        if (isock->getName() == target) {
            Packet *pkt = new Packet();

            QString mData = msg->toString();
            pkt->setData(mData);
            if (m_mode == "server") {
                if (m_clients.contains(target)) {
                    if (target=="*") {
                        foreach(SocketAdapter *isock, m_clients.values()) {
                            sendPacket(isock, pkt);
                        }
                    }
                    else {
                        sendPacket(m_clients[target], pkt);
                    }
                }
            }
            else if (m_mode == "client") {
                if (m_ptcpClient) {
                    sendPacket(m_ptcpClient, pkt);
                }
            }
            else {
                qDebug() << "Mode" << m_mode << "not implemented";
            }
        }
    }
}
