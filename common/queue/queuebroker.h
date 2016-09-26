#ifndef QUEUEBROKER_H
#define QUEUEBROKER_H

#include <QDebug>
#include <QObject>

#include "imessage.h"
#include "query.h"
#include "messagebuilder.h"
#include "subscribe.h"

#include "ilogic.h"
#include "itransport.h"
#include "plugininterface.h"
#include "subscribe.h"
#include "logicqueuebroker.h"


class QueueBroker : public QObject {
    Q_OBJECT
public:
    explicit QueueBroker(QObject *parent);
    void addSubscribe(QString &subscribe);
    void addComponent(ILogic* component);
    void addComponent(ITransport* component);
    void addComponent(PluginInterface* component, QMap<QString, QVariant> params);
    void removeComponent(ITransport* component);
    void removeComponent(ILogic* component);
    void registerRemoteComponent(QString cName, QString rAddress);
    QStringList getRemoteComponentAddress(QString cName);

    void publishComponents(QString transport = QString("Network"), QString target = QString("Broker<*>"));
    QList<Subscribe *> searchSubscribes(QString source, QString mType);
    QList<ITransport *> getTransports(QString trName);
    void removeSubscribes(QString dstTransportName);
private:
    QList<Subscribe*> m_subscribes;

    QMap<QString, ILogic*>      m_components;
    QMap<QString, ITransport*>  m_transports;

    ITransport* getTransport(QString transport);
    ILogic* getLogic(QString logic);

    void routeMessage(IMessage *msg, QString srcTransport);
    bool matchMap(QString src, QString dest);
    QMap<QString, QList<QString>> m_remoteComponents;

    void send(ITransport *tr, IMessage *msg);
public slots:
    // local components messages
    void on_message(IMessage*);
    // transports messages, source = in-transport sender
    void on_message(QString message);
signals:
    // signal to transport for send message
    void message(ITransport*, IMessage*);
};

#endif // QUEUEBROKER_H
