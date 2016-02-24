#ifndef PACKET_H
#define PACKET_H

#include <QObject>

#include "imessage.h"


class Packet : public QObject {
    Q_OBJECT
public:
    explicit Packet(QObject *parent = 0);

    QString sourceTransport;
    QString sourceComponent;
    QString destinationTransport;
    QString destinationComponent;
    IMessage* msg;
    QString toString();
    void fromString(QString msg);
signals:

public slots:
};

#endif // PACKET_H
