#include "subscribe.h"
#include <QStringList>
#include <QDebug>

Subscribe::Subscribe(QObject *parent) : QObject(parent) {

}

Subscribe::Subscribe(QString sub) {
    m_subscribe = sub;
    QStringList coms = sub.split(";");
    if (coms.length() == 4) {
        QStringList source = coms[0].split("::");
        if (source.length() == 1) {
            m_source_transport = normalizeAddress(QString(""));
            m_source_component = normalizeComponentName(source[0]);
        }
        else {
            m_source_transport = normalizeAddress(source[0]);
            m_source_component = normalizeComponentName(source[1]);
        }
        QStringList destination = coms[1].split("::");
        if (destination.length() == 1) {
            m_destination_transport = normalizeAddress(QString(""));
            m_destination_component = normalizeComponentName(destination[0]);
        }
        else {
            m_destination_transport = normalizeAddress(destination[0]);
            m_destination_component = normalizeComponentName(destination[1]);
        }
        m_type = coms[2];
        m_wait_type = coms[3];
    }
    else {
        qDebug() << "Invalid subscribe" << sub;
        qDebug() << "Format: source;destination;message_type;wait_type";
    }
}

QString Subscribe::normalizeAddress(QString addr) {
    QString nAddr;
    if (addr.length() == 0) {
        nAddr = QString("Local<*>");
    }
    else {
        if (addr.contains("<") && addr.contains(">")) {
            QString tAddr = addr.split("<")[1].split(">")[0];
            if (!tAddr.contains(":")) {
                // адрес кривой?
                if (tAddr != "*") {
                    // адрес без порта, заменяем на *
                    tAddr = "<*>";
                }
            }
            nAddr = addr.split("<")[0] + tAddr;
        }
        else {
            // нормализуем
            nAddr = addr + "<*>";
        }
    }
    return nAddr;
}

QString Subscribe::normalizeComponentName(QString cName) {
    QString nName;
    if (cName.length() == 0) {
        nName = QString("Local<*>");
    }
    else {
        if (cName.contains("<") && cName.contains(">")) {
            // self-name defined
            QString selfName = cName.split("<")[1].split(">")[0];
            if (!selfName.contains(":")) {
                selfName = "<" + selfName + ":*>";
            }
            nName = cName.split("<")[0] + selfName;
        }
        else {
            // нормализуем
            nName = cName + "<*>";
        }
    }
    return nName;
}

QString Subscribe::hash() {
    return m_destination_transport + "::" + m_destination_component + ";" + m_type;
}
