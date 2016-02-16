#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QMap>
#include <QDebug>

#include "../common/isocketadapter.h"
#include "clientsocketadapter.h"


class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void send(QString command, QList<QMap<QString, QVariant>>* params);
    void send(QString command, QMap<QString, QVariant>* params);
private:
    void sendCommand(QString command, QMap<QString, QVariant> *params);

signals:

public slots:
    void on_message(QString text);
    void on_send();

protected:
    ISocketAdapter *pSock;
};

#endif // CLIENT_H
