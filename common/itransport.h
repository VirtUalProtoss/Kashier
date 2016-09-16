#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <QObject>

#include "packet.h"
#include "plugininterface.h"


class ITransport : public QObject, public PluginInterface {
    Q_OBJECT
public:
    explicit ITransport(QObject *parent = 0);
    virtual QString getAddress();
    virtual QString getName();
    virtual void setName(QString);
    virtual bool isLocal();
    virtual void send(QString);

signals:

public slots:

protected:
    QString name = QString("ITransport");
};

#endif // ITRANSPORT_H
