#ifndef PACKET_H
#define PACKET_H

#include <QObject>

class Packet : public QObject {
    Q_OBJECT
public:
    explicit Packet(QObject *parent = 0);
    QString toString();
    void fromString(QString pkt);
    void setSourceAddress(QString addr);
    void setDestinationAddress(QString addr);
    void setData(QString pdata);
    inline QString getDestinationAddress() { return destinationAddress; }
    inline int getDestinationPort() { return destinationPort; }
    inline QString getSourceAddress() { return sourceAddress; }
    inline int getSourcePort() { return sourcePort; }
    inline QString getData() { return data; }
private:
    QString sourceAddress;
    int sourcePort;
    QString destinationAddress;
    int destinationPort;
    QString data;
signals:

public slots:
};

#endif // PACKET_H
