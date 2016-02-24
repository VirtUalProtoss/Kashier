#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "../common/logic/ilogic.h"
#include "../common/logic/billing/onyma/onyma.h"
#include "../common/logic/ats/openmn.h"
#include "../common/logic/local/local.h"
#include "../common/queue/queuebroker.h"
#include "serversocketadapter.h"

class QTcpServer;
class QTcpSocket;
class ISocketAdapter;


class Service : public QObject {
    Q_OBJECT
public:
    explicit Service(int nPort, QObject *parent = 0);

    void prepareSubcribes();
    void initComponents();
signals:

public slots:

    void on_newConnection();
    void on_disconnected();
    void on_message(QString msg);
private:
    QList<ISocketAdapter*> m_clients;
    IQueueBroker* broker;
    QTcpServer* m_ptcpServer;
};

#endif // SERVICE_H
