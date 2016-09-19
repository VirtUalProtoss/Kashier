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
        return m_ptcpServer->serverAddress().toString() + ":" + QString(m_ptcpServer->serverPort());
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

    QTextStream(stdout) << "New connection from " << pSockHandle->getAddress() << endl;
    m_clients[pSockHandle->getAddress()] = pSockHandle;
    pSockHandle->setName(QString("Network<" + pSockHandle->getAddress() + QString(">")));
    //m_broker->addComponent(pSockHandle);
    //broker->addComponentMap(pSockHandle, pSockHandle->getName());

    connect(m_broker, 		SIGNAL(message(Packet*)),                   SLOT(on_message(Packet*)));
    connect(pSockHandle, 	SIGNAL(disconnected()), 					SLOT(on_disconnected()));
    connect(this,        	SIGNAL(message(Packet*)), 	m_broker, 		SLOT(receive(Packet*)));
    connect(pSockHandle, 	SIGNAL(message(QString)), 					SLOT(on_message(QString)));

    //QStringList subscribes;
    //subscribes << QString(pSockHandle->getName() + ":Broker;Message<Broker>;Local:Broker;Persist");
    //foreach (QString subscribe, subscribes)
    //    m_broker->addSubscribe(subscribe);
    m_broker->publishComponents();
}

void TransportNetwork::on_disconnected() {

    ServerSocketAdapter* client = static_cast<ServerSocketAdapter*>(sender());
    QTextStream(stdout) << "Client disconnected: " << client->getAddress() << endl;
    m_clients.remove(client->getAddress());
    //m_broker->removeComponent(client);
    delete client;
}

void TransportNetwork::on_message(QString msg) {
    // пришло сетевое сообщение
    ServerSocketAdapter *source = (ServerSocketAdapter*)sender();
    qDebug() << "Network message" << msg << "from" << source->getAddress();
    Packet* pkt = new Packet();
    pkt->fromString(msg);
    emit message(pkt);
}

void TransportNetwork::on_message(Packet *pkt) {
    // Пришел пакет от брокера
    qDebug() << "Broker message" << pkt->toString();
    QString sAddr;
    SocketAdapter* p_sock = 0;
    QString dAddr = pkt->getDestinationAddress() + ":" + QString(pkt->getDestinationPort());
    if (m_mode == "server") {
        sAddr = m_ptcpServer->serverAddress().toString() + ":" + QString(m_ptcpServer->serverPort());
        if (m_clients.contains(dAddr)) {
            p_sock = (SocketAdapter*)m_clients[sAddr];
        }
    }
    else if (m_mode == "client") {
        sAddr = m_ptcpClient->getAddress();
        p_sock = (SocketAdapter*)m_ptcpClient;
    }
    else {
        qDebug() << "Mode" << m_mode << "not implemented";
    }
    pkt->setSourceAddress(sAddr);
    QString msg = pkt->toString();
    if (p_sock) {
        qDebug() << "Sending message" << msg << "to" << dAddr;
        p_sock->sendString(msg);
    }
    else {
        qDebug() << "No such socket address" << dAddr;
    }
}

void TransportNetwork::disconnect() {
    // TODO: unregister remote transports, components, subscribes, notify local components
    ;
}

void TransportNetwork::on_init_complete() {
    m_broker = static_cast<QueueBroker*>(this->parent());
    QString mode = "server";
    if (_initParams->contains("mode"))
        mode = _initParams->value("mode").toString();
    changeMode(mode, *_initParams);
}
