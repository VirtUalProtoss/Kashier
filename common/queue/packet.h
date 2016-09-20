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
    inline void setSourceAddress(QString address, int port) { sourceAddress = address; sourcePort = port; }
    inline void setDestinationAddress(QString address, int port) { destinationAddress = address; destinationPort = port; }
    void setDestinationAddress(QString addr);
    inline void setData(QString pdata) { data = pdata; }
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
