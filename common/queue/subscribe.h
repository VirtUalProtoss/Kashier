#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include <QDateTime>

#include "uri.h"

class Subscribe {
public:
    explicit Subscribe();
    Subscribe(QString sub);
    Subscribe(const Subscribe&);

    inline URI getSource() { return m_source; }
    inline URI getDestination() { return m_destination; }
    inline void setDestination(URI dest) { m_destination = dest; }
    inline void setSource(URI src) { m_source = src; }
    inline QString getType() { return m_type; }
    QString getHash();
    QString toString() { return m_subscribe; }
    bool isTimeout();
    bool addrMatch(URI destination);
private:
    QString m_subscribe = QString("");
    QString m_type;
    QString m_wait_type;
    QDateTime m_addTime;
    QDateTime m_removeTime;
    URI m_source;
    URI m_destination;
};

#endif // SUBSCRIBE_H
