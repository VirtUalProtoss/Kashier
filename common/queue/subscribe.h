#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include <QDateTime>

class Subscribe {
public:
    explicit Subscribe();
    Subscribe(QString sub);

    inline QString getSource() { return m_source_address + "::" + m_source_transport + "::" + m_source_component; }
    inline QString getDestination() { return m_destination_address + "::" + m_destination_transport + "::" + m_destination_component; }
    inline QString getDestinationAddress() { return m_destination_address; }
    inline QString getDestinationTransport() { return m_destination_transport; }
    inline QString getDestinationComponent() { return m_destination_component; }
    inline QString getSourceAddress() { return m_source_address; }
    inline QString getSourceTransport() { return m_source_transport; }
    inline QString getSourceComponent() { return m_source_component; }
    inline QString getType() { return m_type; }
    QString getHash();
    QString toString() { return m_subscribe; }
    bool isTimeout();
    bool addrMatch(QString source, QString destination);

private:
    QString m_subscribe;
    QString m_source_address;
    QString m_source_transport;
    QString m_source_component;
    QString m_destination_address;
    QString m_destination_transport;
    QString m_destination_component;
    QString m_type;
    QString m_wait_type;
    QDateTime m_addTime;
    QDateTime m_removeTime;
};

#endif // SUBSCRIBE_H
