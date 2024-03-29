#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <QObject>

#include "packet.h"

class QueueBroker;

class ITransport : public QObject {
    Q_OBJECT
public:
    explicit ITransport(QObject *parent = 0);
    virtual QString getAddress();
    virtual QString getRemoteAddress();
    virtual QString getName();
    virtual void setName(QString);
    virtual bool isLocal();
    virtual bool isLocalAddress(QString address);
    virtual void send(QString);
    QString getType() { return QString("Transport"); }
    virtual void setInitParams(QMap<QString, QVariant>* initParams);

signals:
    void init_complete();

public slots:

protected:
    QString name = QString("ITransport");
    QMap<QString, QVariant>* _initParams;
    QueueBroker* m_broker;
};

#endif // ITRANSPORT_H
