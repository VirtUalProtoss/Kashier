#include "subscribe.h"
#include <QStringList>
#include <QDebug>
#include "uri.h"

Subscribe::Subscribe(QObject *parent) : QObject(parent) {

}

Subscribe::Subscribe(QString sub) {
    m_subscribe = sub;
    QStringList coms = sub.split(";");
    if (coms.length() == 4) {
        QStringList source = coms[0].split("::");
        if (source.length() == 1) {
            m_source_transport = URI::normalizeAddress(QString(""));
            m_source_component = URI::normalizeComponentName(source[0]);
        }
        else {
            m_source_transport = URI::normalizeAddress(source[0]);
            m_source_component = URI::normalizeComponentName(source[1]);
        }
        QStringList destination = coms[1].split("::");
        if (destination.length() == 1) {
            m_destination_transport = URI::normalizeAddress(QString(""));
            m_destination_component = URI::normalizeComponentName(destination[0]);
        }
        else {
            m_destination_transport = URI::normalizeAddress(destination[0]);
            m_destination_component = URI::normalizeComponentName(destination[1]);
        }
        m_type = coms[2];
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
