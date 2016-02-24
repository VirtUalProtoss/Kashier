#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QMap>
#include <QDebug>

#include "../common/transport/isocketadapter.h"
#include "clientsocketadapter.h"

#include "../common/logic/ilogic.h"
#include "../common/logic/kkm/kkm.h"
#include "../common/logic/local/local.h"
#include "../common/logic/gui/gui.h"
#include "../common/queue/queuebroker.h"


class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void initComponents();
    void prepareSubcribes();

protected:
    ISocketAdapter *pSock;
    IQueueBroker* broker;
};

#endif // CLIENT_H
