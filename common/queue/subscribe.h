#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include <QObject>

class Subscribe : public QObject {
    Q_OBJECT
public:
    explicit Subscribe(QObject *parent = 0);
    Subscribe(QString sub);
    QString normalizeAddress(QString addr);
    QString normalizeComponentName(QString cName);
    QString getSource() { return m_source_transport + "::" + m_source_component; }
    QString getType() { return m_type; }
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
};

#endif // SUBSCRIBE_H
