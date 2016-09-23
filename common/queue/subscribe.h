#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include <QObject>
#include <QDateTime>

class Subscribe : public QObject {
    Q_OBJECT
public:
    explicit Subscribe(QObject *parent = 0);
    Subscribe(QString sub);

    QString getSource() { return m_source_transport + "::" + m_source_component; }
    QString getDestination() { return m_destination_transport + "::" + m_destination_component; }
    QString getDestinationTransport() { return m_destination_transport; }
    QString getType() { return m_type; }
    QString hash();
    QString toString() { return m_subscribe; }
signals:

public slots:
private:
    QString m_subscribe;
    QString m_source_transport;
    QString m_source_component;
    QString m_destination_transport;
    QString m_destination_component;
    QString m_type;
    QString m_wait_type;
    QDateTime m_addTime;
    QDateTime m_removeTime;
};

#endif // SUBSCRIBE_H
