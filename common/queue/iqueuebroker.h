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
    virtual void send(IMessage* message);
    virtual void receive(IMessage* message);
    virtual void subscribe(
            ITransport* sourceTransport,
            ILogic* sourceComponent,
            IMessage* messageType,
            ITransport* destinationTransport,
            ILogic* destinationComponent);
signals:

public slots:
};

#endif // IQUEUEBROKER_H
