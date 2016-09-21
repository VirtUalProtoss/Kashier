#include "transportnetwork.h"

TransportNetwork::TransportNetwork(QObject *parent) : ITransport(parent) {
    m_broker = static_cast<QueueBroker*>(parent);
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
        m_ptcpClient = new ClientSocketAdapter(this);

        connect(m_ptcpClient, 	SIGNAL(disconnected()),     m_ptcpClient, 	SLOT(disconnect()));
        connect(m_ptcpClient, 	SIGNAL(message(QString)),                   SLOT(on_message(QString)));

        connect(m_broker, 		SIGNAL(message(Packet*)),                   SLOT(on_message(Packet*)));
        connect(this,        	SIGNAL(message(Packet*)), 	m_broker,       SLOT(receive(Packet*)));

        if (params.contains("address")){
            QString addr = params["address"].toString();
            int port = 8765;
            if (params.contains("port")) port = params["port"].toInt();
            m_ptcpClient->connect(addr, port);
        }
        else {
            qDebug() << "No connection data specified";
        }

        m_broker->publishComponents();
    }
    if (mode=="proxy") {
        ;
    }
}

QString TransportNetwork::getName() {

    return QString("Network");
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
    ServerSocketAdapter *pSockHandle = new ServerSocketAdapter(pclientSock);


    QString fullAddr = pSockHandle->getAddress() + ":" + QString::number(pSockHandle->getPort());
    QTextStream(stdout) << "New connection from " << fullAddr << endl;
    pSockHandle->setName(QString("Broker<") + fullAddr + QString(">"));
    m_clients[pSockHandle->getName()] = pSockHandle;

    connect(m_broker, 		SIGNAL(message(ITransport*, IMessage*)),    pSockHandle,  SLOT(on_message(ITransport *, IMessage *)));
    connect(pSockHandle,	SIGNAL(message(ITransport*, IMessage*)),    SLOT(on_message(ITransport *, IMessage *)));
    connect(pSockHandle, 	SIGNAL(disconnected()), 					SLOT(on_disconnected()));
    connect(this,        	SIGNAL(message(Packet*, QString)), 	m_broker, 		SLOT(receive(Packet*, QString)));
    connect(pSockHandle, 	SIGNAL(message(QString)), 					SLOT(on_message(QString)));

    QStringList subscribes;
    subscribes << QString("Network::" + pSockHandle->getName() + ";Message<Broker>;Broker;Persist");
    foreach (QString subscribe, subscribes)
        m_broker->addSubscribe(subscribe);
    m_broker->publishComponents(getName(), pSockHandle->getName());
}

void TransportNetwork::on_disconnected() {

    ServerSocketAdapter* client = static_cast<ServerSocketAdapter*>(sender());
    QTextStream(stdout) << "Client disconnected: " << client->getName() << endl;
    m_clients.remove(client->getName());
    m_broker->removeSubscriptions(client->getName());
    delete client;
}

void TransportNetwork::on_message(QString msg) {
    // пришло сетевое сообщение
    ServerSocketAdapter *source = (ServerSocketAdapter*)sender();
    qDebug() << "Network message" << msg << "from" << source->getAddress();
    Packet* pkt = new Packet();
    pkt->fromString(msg);

    emit message(pkt, source->getName());
}

void TransportNetwork::on_message(Packet *pkt) {
    // Пришел пакет от брокера
    qDebug() << "Broker message" << pkt->toString();
    QString dstAddr = pkt->getDestinationAddress();
    QString dAddr = dstAddr + ":" + QString::number(pkt->getDestinationPort());
    QString msg = QString("");

    if (m_mode == "server") {


        if (dstAddr == QString("0.0.0.0")) {
            foreach (ISocketAdapter *mc_sock, m_clients.values()) {
                ServerSocketAdapter * srvSock = (ServerSocketAdapter *)mc_sock;
                pkt->setSourceAddress(srvSock->getLocalAddress(), srvSock->getLocalPort());
                pkt->setDestinationAddress(srvSock->getAddress(), srvSock->getPort());
                msg = pkt->toString();
                qDebug() << "Sending message" << msg << "to" << srvSock->getName();
                mc_sock->sendString(msg);
            }
        }
        else {
            if (m_clients.contains(dAddr)) {
                ServerSocketAdapter * srvSock = (ServerSocketAdapter *)m_clients[dAddr];
                pkt->setSourceAddress(srvSock->getLocalAddress(), srvSock->getLocalPort());
                pkt->setDestinationAddress(srvSock->getAddress(), srvSock->getPort());
                msg = pkt->toString();
                qDebug() << "Sending message" << msg << "to" << srvSock->getName();
                m_clients[dAddr]->sendString(msg);
            }
        }
    }
    else if (m_mode == "client") {
        pkt->setSourceAddress(m_ptcpClient->getAddress(), m_ptcpClient->getPort());
        pkt->setDestinationAddress(m_ptcpClient->getRemoteAddress(), m_ptcpClient->getRemotePort());
        msg = pkt->toString();
        qDebug() << "Sending message" << msg << "to" << m_ptcpClient->getName();
        m_ptcpClient->sendString(msg);
    }
    else {
        qDebug() << "Mode" << m_mode << "not implemented";
    }
}

void TransportNetwork::disconnect() {
    // TODO: unregister remote transports, components, subscribes, notify local components
    ClientSocketAdapter* client = static_cast<ClientSocketAdapter*>(sender());
    QTextStream(stdout) << "Client disconnected" << client->getName() << endl;
}

void TransportNetwork::on_init_complete() {
    m_broker = static_cast<QueueBroker*>(this->parent());
    QString mode = "server";
    if (_initParams->contains("mode"))
        mode = _initParams->value("mode").toString();
    changeMode(mode, *_initParams);
}

void sendPacket(ServerSocketAdapter *sock, Packet *pkt) {
    if (sock->isConnected()) {
        qDebug() << "Send message" << pkt->getData() << "to" << sock->getName();
        pkt->setDestinationAddress(sock->getAddress(), sock->getPort());
        pkt->setSourceAddress(sock->getLocalAddress(), sock->getLocalPort());
        sock->sendString(pkt->toString());
    }
    else {
        qDebug() << "Socket" << sock->getName() << "disconnected";
    }
}

void TransportNetwork::on_message(ITransport *tr, IMessage *msg) {
    ServerSocketAdapter *isock = static_cast<ServerSocketAdapter*>(sender());
    if (tr==this) {
        QString target = msg->getTarget();
        if (isock->getName() == target) {
            Packet *pkt = new Packet();

            QString mData = msg->toString();
            pkt->setData(mData);
            if (m_mode=="server") {
                if (m_clients.contains(target)) {
                    if (target=="*") {
                        foreach(ISocketAdapter *isock, m_clients.values()) {
                            ServerSocketAdapter *sock = (ServerSocketAdapter *)isock;
                            sendPacket(sock, pkt);
                        }
                    }
                    else {
                        ServerSocketAdapter *sock = (ServerSocketAdapter *)m_clients[target];
                        sendPacket(sock, pkt);
                    }
                }
            }
            else if (m_mode=="client") {
                if (m_ptcpClient) {
                    if (m_ptcpClient->isConnected()) {
                        qDebug() << "Send message" << pkt->getData() << "to" << m_ptcpClient->getName();
                        pkt->setDestinationAddress(m_ptcpClient->getRemoteAddress(), m_ptcpClient->getRemotePort());
                        pkt->setSourceAddress(m_ptcpClient->getAddress(), m_ptcpClient->getPort());
                        m_ptcpClient->sendString(pkt->toString());
                    }
                    else {
                        qDebug() << "Client disconnected";
                    }
                }
            }
            else {
                qDebug() << "Mode" << m_mode << "not implemented";
            }
        }
    }
}
