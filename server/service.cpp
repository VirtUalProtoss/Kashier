#include "service.h"

Service::Service(int nPort, QObject *parent) : QObject(parent), broker(new QueueBroker(this)), m_ptcpServer(new QTcpServer(this)) {
    connect(m_ptcpServer, SIGNAL(newConnection()), SLOT(on_newConnection()));

    if (false == m_ptcpServer->listen(QHostAddress::AnyIPv4, nPort)) {
        m_ptcpServer->close();
        throw m_ptcpServer->errorString();
    }

}

void Service::on_newConnection() {
    QTcpSocket* pclientSock = m_ptcpServer->nextPendingConnection();
    ISocketAdapter *pSockHandle = new ServerSocketAdapter(pclientSock);

    m_clients.push_back(pSockHandle);

    QTextStream(stdout) << "New connection from " << pSockHandle->getAddress() << endl;
    pSockHandle->setName(QString("Network<" + pSockHandle->getAddress() + QString(">")));
    broker->addComponent(pSockHandle);
    //broker->addComponentMap(pSockHandle, pSockHandle->getName());
    //pSockHandle->sendString("connect");

    connect(pSockHandle, SIGNAL(disconnected()), SLOT(on_disconnected()));
    connect(pSockHandle, SIGNAL(message(QString)), broker, SLOT(receive(QString)));
    connect(pSockHandle, SIGNAL(message(QString)), SLOT(on_message(QString)));
    connect(broker, SIGNAL(network_message(QString)), pSockHandle, SLOT(on_send(QString))); // broadcast messages

    QStringList subscribes;
    subscribes << QString(pSockHandle->getName() + ":Broker;Message<Broker>;Local:Broker;Persist");
    foreach (QString subscribe, subscribes)
        broker->addSubscribe(subscribe);
    broker->publishComponents();
}

void Service::on_disconnected() {

    ISocketAdapter* client = static_cast<ServerSocketAdapter*>(sender());
    QTextStream(stdout) << "Client disconnected: " << client->getAddress() << endl;
    m_clients.removeOne(client);
    broker->removeComponent(client);
    delete client;
}

void Service::on_message(QString msg) {
    ServerSocketAdapter *target = (ServerSocketAdapter*)sender();
    qDebug() << target->getAddress() << ":" << msg;
    target->sendString(msg);
}

void Service::initComponents() {
    qDebug() << "Service::initComponents()";

    ILogic* ats = new OpenMN(this);
    ILogic* local = new Local(this);
    ILogic* billing = new Onyma(this);
    //connect(billing, SIGNAL(message(IMessage*)), billing, SLOT(emit_message(IMessage*)));
    ITransport* tLocal = new TransportLocal(this);

    broker->addComponent(ats);
    broker->addComponent(local);
    broker->addComponent(billing);
    broker->addComponent(tLocal);

    broker->addComponentMap(tLocal, ats);
    broker->addComponentMap(tLocal, billing);
    broker->addComponentMap(tLocal, local);

}

void Service::prepareSubcribes() {
    QStringList subscribes;
    subscribes << QString("Local:Broker;Message;Local:Broker;Persist");
    subscribes << QString("Local:Billing;Query:Billing;Network:Billing;Persist");
    subscribes << QString("Local:Billing;Reply;Local:Local;Persist");
    subscribes << QString("Network:Billing;Reply;Local:Local;Persist");
    //subscribes << QString("Local:KKM;Reply;Local:Local;Persist");
    foreach (QString subscribe, subscribes)
        broker->addSubscribe(subscribe);
}
