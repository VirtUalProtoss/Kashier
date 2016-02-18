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
    void send(QString command, QList<QMap<QString, QVariant>>* params);
    void send(QString command, QMap<QString, QVariant>* params);
    void initComponents();
    void prepareSubcribes();
private:
    void sendCommand(QString command, QMap<QString, QVariant> *params);

signals:

public slots:
    void on_message(QString text);
    void on_send();

protected:
    ISocketAdapter *pSock;
    IQueueBroker* broker;
};

#endif // CLIENT_H
