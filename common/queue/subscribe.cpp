#include "subscribe.h"
#include <QStringList>
#include <QDebug>
#include "uri.h"

Subscribe::Subscribe(QObject *parent) : QObject(parent) {

}

Subscribe::Subscribe(QString sub) {
    m_subscribe = sub;
    QStringList coms = m_subscribe.split(";");
    if (coms.length() == 4) {
        m_source_transport = URI::getTransport(coms[0]);
        m_source_component = URI::getComponent(coms[0]);
        m_destination_transport = URI::getTransport(coms[1]);
        m_destination_component = URI::getComponent(coms[1]);
        m_type = URI::getComponent(coms[2]);
        m_wait_type = coms[3];
    }
    else {
        qDebug() << "Invalid subscribe" << sub;
        qDebug() << "Format: source;destination;message_type;wait_type";
    }

}

QString Subscribe::hash() {
    return m_destination_transport + "::" + m_destination_component + ";" + m_type;
}
