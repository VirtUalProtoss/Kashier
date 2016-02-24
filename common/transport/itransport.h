#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <QObject>

#include "../queue/packet.h"


class ITransport : public QObject {
    Q_OBJECT
public:
    explicit ITransport(QObject *parent = 0);
    QString getAddress();
    QString getName();
    bool isLocal();
    void send(QString data);
signals:

public slots:
};

#endif // ITRANSPORT_H
