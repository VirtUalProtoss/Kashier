#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include <QDateTime>

#include "uri.h"

class Subscribe {
public:
    explicit Subscribe();
    Subscribe(QString sub);

    inline URI getSource() { return m_source; }
    inline URI getDestination() { return m_destination; }
    inline QString getType() { return m_type; }
    QString getHash();
    QString toString() { return m_subscribe; }
    bool isTimeout();
    bool addrMatch(QString source, QString destination);

private:
    QString m_subscribe;
    /*
    QString m_source_address;
    QString m_source_transport;
    QString m_source_component;
    QString m_destination_address;
    QString m_destination_transport;
    QString m_destination_component;
    */
    QString m_type;
    QString m_wait_type;
    QDateTime m_addTime;
    QDateTime m_removeTime;
    URI m_source;
    URI m_destination;
};

#endif // SUBSCRIBE_H
