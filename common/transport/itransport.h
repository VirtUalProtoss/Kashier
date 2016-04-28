#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <QObject>

#include "../queue/packet.h"


class ITransport : public QObject {
    Q_OBJECT
public:
    explicit ITransport(QObject *parent = 0);
    virtual QString getAddress();
    virtual QString getName();
    virtual bool isLocal();
    virtual void send(QString);
    virtual void setName(QString);
signals:

public slots:

protected:
    QString name = QString("ITransport");
};

#endif // ITRANSPORT_H
