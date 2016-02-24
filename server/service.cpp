#include "service.h"

Service::Service(int nPort, QObject *parent) : QObject(parent), broker(new QueueBroker(this)), m_ptcpServer(new QTcpServer(this))
{
    connect(m_ptcpServer, SIGNAL(newConnection()), SLOT(on_newConnection()));

    if (false == m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        m_ptcpServer->close();
        throw m_ptcpServer->errorString();
    }

}

void Service::on_newConnection() {
    QTextStream(stdout) << "new connection" << endl;

    QTcpSocket* pclientSock = m_ptcpServer->nextPendingConnection();
    ISocketAdapter *pSockHandle = new ServerSocketAdapter(pclientSock);

    m_clients.push_back(pSockHandle);
    broker->addComponent(pSockHandle);

    pSockHandle->sendString("connect");

    connect(pSockHandle, SIGNAL(disconnected()), SLOT(on_disconnected()));
    connect(pSockHandle, SIGNAL(message(QString)), SLOT(on_message(QString)));
    connect(pSockHandle, SIGNAL(message(QString)), broker, SLOT(receive(QString)));
}

void Service::on_disconnected() {
    QTextStream(stdout) << "client disconnected" << endl;
    ISocketAdapter* client = static_cast<ServerSocketAdapter*>(sender());
    m_clients.removeOne(client);
    broker->removeComponent(client);
    delete client;
}

void Service::on_message(QString msg) {
    qDebug() << ((ServerSocketAdapter*)sender())->getAddress() << ":" << msg;
}

void Service::initComponents() {
    ILogic* ats = new OpenMN(this);
    ILogic* local = new Local(this);
    ILogic* billing = new Onyma(this);
    broker->addComponent(ats);
    broker->addComponent(local);
    broker->addComponent(billing);
}

void Service::prepareSubcribes() {
    QStringList subscribes;
    foreach (QString subscribe, subscribes)
        broker->addSubscribe(subscribe);
}
