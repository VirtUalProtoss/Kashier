#ifndef LOGICQUEUEBROKER_H
#define LOGICQUEUEBROKER_H

#include <QString>
#include "ilogic.h"

class IMessage;

class LogicQueueBroker : public ILogic {
public:
    LogicQueueBroker(QObject *parent = 0);
    inline QString getName() { return QString("Broker"); }
    void receive(IMessage*);
};

#endif // LOGICQUEUEBROKER_H
