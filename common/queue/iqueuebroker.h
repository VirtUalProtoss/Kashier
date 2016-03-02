#ifndef IQUEUEBROKER_H
#define IQUEUEBROKER_H

#include <QObject>

#include "imessage.h"
#include "../logic/ilogic.h"
#include "../transport/itransport.h"


class IQueueBroker : public QObject {
    Q_OBJECT
public:
    explicit IQueueBroker(QObject *parent);
    virtual void startBroking();
    virtual void addSubscribe(QString &subscribe);
    virtual void addComponent(ILogic* component);
    virtual void addComponent(ITransport* component);
    virtual void removeComponent(ITransport* component);
    virtual void removeComponent(ILogic* component);
    virtual void publishComponents();
    virtual void addComponentMap(ITransport* transport, ILogic* component);
    virtual void addComponentMap(ITransport *transport, QString component);
    virtual void registerRemoteSubscribe(QString key, QString sub);
signals:
    void network_message(QString);
public slots:
    virtual void send(IMessage *message);
    virtual void receive(IMessage *message);
    virtual void receive(QString message);
};

#endif // IQUEUEBROKER_H
