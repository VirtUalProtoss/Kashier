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
public slots:
    void on_init_complete();
};

#endif // LOGICQUEUEBROKER_H
