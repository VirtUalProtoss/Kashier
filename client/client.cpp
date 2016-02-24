#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent),
    pSock(new ClientSocketAdapter(this)),
    broker(new QueueBroker(this))
{

}

void Client::initComponents() {
    ILogic* kkm = new KKM(this);
    ILogic* local = new Local(this);
    ILogic* gui = new GUI(this);
//    ITransport* tLocal = new ITransport(this);
    broker->addComponent(kkm);
    broker->addComponent(local);
    broker->addComponent(gui);
    broker->addComponent(pSock);
//    broker->addComponentMap(tLocal, kkm);
//    broker->addComponentMap(tLocal, local);
//    broker->addComponentMap(tLocal, gui);


}

void Client::prepareSubcribes() {
    QStringList subscribes;
    subscribes << QString("Local:GUI;Query:Billing;Network<127.0.0.1>:Billing;Persist");
    subscribes << QString("Local:GUI;Query:KKM;Local:Local;Persist");
    subscribes << QString("Network:Billing;Reply;Local:Local;Persist");
    subscribes << QString("Local:KKM;Reply;Local:Local;Persist");
    foreach (QString subscribe, subscribes)
        broker->addSubscribe(subscribe);
}
