#include "transportnetwork.h"
#include "uri.h"

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

bool TransportNetwork::isLocalAddress(QString address) {
    bool local = false;
    if (m_mode == "server") {
        QString lAddress = QString("");
        foreach (SocketAdapter* client, m_clients) {
            lAddress = client->getLocalAddress() + QString::number(client->getLocalPort());
            if (lAddress == address)
                local = true;
        }
    }
    else if (m_mode == "client") {
        QString lAddress = m_ptcpClient->getLocalAddress() + ":" + QString::number(m_ptcpClient->getLocalPort());
        if (lAddress == address)
            local = true;
    }
    else {
        qDebug() << "Mode" << m_mode << "not implemented";
    }
    return local;
}

void TransportNetwork::on_newConnection() {
    QTcpSocket* pclientSock = m_ptcpServer->nextPendingConnection();
    SocketAdapter *pSockHandle = new SocketAdapter(this, pclientSock);


    QString fullAddr = pSockHandle->getRemoteAddress() + ":" + QString::number(pSockHandle->getRemotePort());
    QTextStream(stdout) << "New connection from " << fullAddr << endl;
    pSockHandle->setName(QString("Network<") + fullAddr + QString(">"));
    m_clients[pSockHandle->getName()] = pSockHandle;

    connect(m_broker, 		SIGNAL(message(ITransport*, IMessage*)),    pSockHandle,  SLOT(on_message(ITransport *, IMessage *)));
    connect(pSockHandle,	SIGNAL(sock_message(ITransport*, IMessage*)),    SLOT(on_broker_message(ITransport *, IMessage *)));
    connect(pSockHandle, 	SIGNAL(disconnected()), 					SLOT(on_disconnected()));
    connect(this,        	SIGNAL(message(QString)), 	m_broker, 		SLOT(on_message(QString)));
    connect(pSockHandle, 	SIGNAL(message(QString)), 					SLOT(on_network_message(QString)));

    QStringList subscribes;
    //subscribes << getName() + QString("::") + pSockHandle->getName() + QString(";Broker;Message;Persist");
    subscribes << pSockHandle->getName() + QString("::Broker;Broker;Message;Persist");
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
    //SocketAdapter* client = static_cast<SocketAdapter*>(sender());
    m_ptcpClient = static_cast<SocketAdapter*>(sender());
    QString fullAddr = m_ptcpClient->getLocalAddress() + ":" + QString::number(m_ptcpClient->getLocalPort());
    m_ptcpClient->setName(QString("Network<") + fullAddr + QString(">"));

    qDebug() << "Connect to server:" << fullAddr << m_ptcpClient->isConnected();
    m_broker->addComponent(this);

    QStringList subscribes;
    //subscribes << getName() + QString("::") + client->getName() + QString(";Broker;Message;Persist");
    subscribes << m_ptcpClient->getName() + QString("::Broker;Broker;Message;Persist");
    foreach (QString subscribe, subscribes)
        m_broker->addSubscribe(subscribe);
    m_broker->publishComponents(getName(), m_ptcpClient->getName());
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

void TransportNetwork::sendSockMessage(SocketAdapter *sock, IMessage *msg) {
    if (sock->isConnected()) {
        QString sender = QString("Network<") + sock->getLocalAddress() + ":" + QString::number(sock->getLocalPort()) + QString(">");
        msg->setSender(sender + QString("::") + msg->getSender());
        if (URI::getTransportAddress(msg->getTarget()) == "*") {
            msg->setTarget(sock->getRemoteName() + "::" + msg->getTarget());
        }
        Packet *pkt = new Packet();
        pkt->setData(msg->toString());
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
    if (tr == this) {
        QString target = URI::getTransportAddress(msg->getTarget());
        if (target.length() > 0) {
            if (m_mode == "server") {

                if (target == "*") {
                    foreach(SocketAdapter *isock, m_clients.values()) {
                        sendSockMessage(isock, msg);
                    }
                }
                else {
                    if (m_clients.contains(target))
                        sendSockMessage(m_clients[target], msg);
                }

            }
            else if (m_mode == "client") {

                if (isock->getName() == target || target == "*") {
                    if (m_ptcpClient)
                        sendSockMessage(m_ptcpClient, msg);
                }
                else {
                    if (isock->isConnected())
                        qDebug() << "Socket" << isock->getName() << "not match target" << target;
                    else
                        qDebug() << "Socket disconnected";
                }

            }
            else
                qDebug() << "Mode" << m_mode << "not implemented";
        }
        else {
            qDebug() << "No such address" << msg->getTarget();
        }
    }
}
