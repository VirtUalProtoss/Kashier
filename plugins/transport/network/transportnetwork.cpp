#include "transportnetwork.h"

TransportNetwork::TransportNetwork(QObject *parent) : ITransport(parent) {
	QString mode;
	if (mode=="server") {
		m_ptcpServer = new QTcpServer(this);
		connect(m_ptcpServer, SIGNAL(newConnection()), SLOT(on_newConnection()));
	}
	if (mode=="client") {
		m_ptcpClient = new ClientSocketAdapter(this);
		connect(parent(), 		SIGNAL(network_message(QString)), 	m_ptcpClient, 	SLOT(on_send(QString)));
	    connect(m_ptcpClient, 	SIGNAL(disconnected()), 			m_ptcpClient, 	SLOT(disconnect()));
	    connect(m_ptcpClient, 	SIGNAL(message(QString)), 			parent(), 		SLOT(receive(QString)));
	}
	if (mode=="proxy") {
		;
	}
}

QString TransportNetwork::getName() {

    return QString("Network");
}

QString TransportNetwork::getAddress() {

    return QString("127.0.0.1");
}

void TransportNetwork::on_newConnection() {
    QTcpSocket* pclientSock = m_ptcpServer->nextPendingConnection();
    ISocketAdapter *pSockHandle = new ServerSocketAdapter(pclientSock);

    m_clients.push_back(pSockHandle);

    QTextStream(stdout) << "New connection from " << pSockHandle->getAddress() << endl;
    pSockHandle->setName(QString("Network<" + pSockHandle->getAddress() + QString(">")));
    parent()->addComponent(pSockHandle);
    //broker->addComponentMap(pSockHandle, pSockHandle->getName());
    //pSockHandle->sendString("connect");

    connect(pSockHandle, 	SIGNAL(disconnected()), 							SLOT(on_disconnected()));
    connect(pSockHandle, 	SIGNAL(message(QString)), 			parent(), 		SLOT(receive(QString)));
    connect(pSockHandle, 	SIGNAL(message(QString)), 							SLOT(on_message(QString)));
    connect(parent(), 		SIGNAL(network_message(QString)), 	pSockHandle, 	SLOT(on_send(QString))); // broadcast messages

    QStringList subscribes;
    subscribes << QString(pSockHandle->getName() + ":Broker;Message<Broker>;Local:Broker;Persist");
    foreach (QString subscribe, subscribes)
        parent()->addSubscribe(subscribe);
    parent()->publishComponents();
}

void TransportNetwork::on_disconnected() {

    ISocketAdapter* client = static_cast<ServerSocketAdapter*>(sender());
    QTextStream(stdout) << "Client disconnected: " << client->getAddress() << endl;
    m_clients.removeOne(client);
    parent()->removeComponent(client);
    delete client;
}

void TransportNetwork::on_message(QString msg) {
    ServerSocketAdapter *target = (ServerSocketAdapter*)sender();
    qDebug() << target->getAddress() << ":" << msg;
    target->sendString(msg);
}

void TransportNetwork::disconnect() {

    ;
}