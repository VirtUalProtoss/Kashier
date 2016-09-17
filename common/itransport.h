#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <QObject>

#include "packet.h"

class ITransport : public QObject {
    Q_OBJECT
public:
    explicit ITransport(QObject *parent = 0);
    virtual QString getAddress();
    virtual QString getName();
    virtual void setName(QString);
    virtual bool isLocal();
    virtual void send(QString);
    QString getType() { return QString("Transport"); }

signals:

public slots:

protected:
    QString name = QString("ITransport");
};

#endif // ITRANSPORT_H
