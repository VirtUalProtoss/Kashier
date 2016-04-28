#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent),
    pSock(new ClientSocketAdapter(this)),
    broker(new QueueBroker(this))
{

}

void Client::publishComponents() {
    broker->publishComponents();
}

void Client::initComponents() {
    ILogic* kkm = new KKM(this);
    ILogic* local = new Local(this);
    ILogic* gui = new GUI(this);
    ITransport* tLocal = new TransportLocal(this);
    broker->addComponent(kkm);
    broker->addComponent(local);
    broker->addComponent(gui);
    broker->addComponent(tLocal);
    broker->addComponent(pSock);
    broker->addComponentMap(tLocal, kkm);
    broker->addComponentMap(tLocal, local);
    broker->addComponentMap(tLocal, gui);

    connect(broker, SIGNAL(network_message(QString)), pSock, SLOT(on_send(QString)));
    connect(pSock, SIGNAL(disconnected()), pSock, SLOT(disconnect()));
    connect(pSock, SIGNAL(message(QString)), broker, SLOT(receive(QString)));
}

void Client::prepareSubcribes() {

    QString netAddr = QString("127.0.0.1");
    if (pSock->isConnected()) {
        netAddr = pSock->getAddress();
    }
    qDebug() << netAddr;
    QStringList subscribes;
    subscribes << QString("Network<" + netAddr + ">:Broker;Message<Broker>;Local:Broker;Persist");
    subscribes << QString("Local:GUI<MainWindow>;Query:Onyma;Network<" + netAddr + ">:Onyma;Persist");
    subscribes << QString("Local:GUI<LoginWindow>;Query:Onyma;Network<" + netAddr + ">:Onyma;Persist");
    subscribes << QString("Local:GUI<PaymentWindow>;Query:KKM;Local:Local;Persist");
    subscribes << QString("Network<" + netAddr + ">:Onyma;Reply;Local:Local;Persist");
    subscribes << QString("Local:KKM;Reply;Local:Local;Persist");
    foreach (QString subscribe, subscribes)
        broker->addSubscribe(subscribe);

    QMap<QString, QString> remoteSubscribes;
    remoteSubscribes["GUI<MainWindow>"] = QString("Network<" + netAddr + ">:GUI<MainWindow>;Query:Onyma;Local:Onyma;Persist");
    remoteSubscribes["GUI<LoginWindow>"] = QString("Network<" + netAddr + ">:GUI<LoginWindow>;Query:Onyma;Local:Onyma;Persist");
    //remoteSubscribes["GUI<PaymentWindow>"] = QString("Network<" + netAddr + ">:GUI<PaymentWindow>;Query:KKM;Local:Local;Persist");
    //remoteSubscribes["KKM"] = QString("Network<" + netAddr + ">:KKM;Query:KKM;Local:Local;Persist");
    //remoteSubscribes["Onyma"] = QString("Local:Onyma;Reply;Network<" + netAddr + ">:Local;Persist");
    foreach (QString key, remoteSubscribes.keys())
        broker->registerRemoteSubscribe(key, remoteSubscribes[key]);
}
