#include "uri.h"

URI::URI() {
    m_uri = QString("");
}

/*
    URI format:
    [transport_name[<address:port>|<*>]{=Local<*>}::]component_name[<self_name[:{instance_id|thread_id}>]]{=<*>}

*/

URI::URI(QString uri) {
    m_uri = uri;
    QStringList parts = m_uri.split("::");

    if (parts.length() == 0) {
        m_uri = QString("");
    }
    else if (parts.length() == 1) {
        // Transport = Local<*>
        m_transport = getName(QString(""));
        m_address = getParam(m_transport);
        m_component = getName(parts[0]);
        m_component_instance = getParam(parts[0]);
    }
    else if (parts.length() == 2) {
        m_transport = getName(parts[0]);
        m_address = getParam(parts[0]);
        m_component = getName(parts[1]);
        m_component_instance = getParam(parts[1]);
    }
    else {
        m_uri = QString("");
    }
}

QString URI::getURI(QString transport, QString component, QMap<QString, QVariant> params) {
    QString pstr;
    foreach (QString param, params.keys()) {
        pstr += param + "=" + params.value(param).toString();
    }
    return transport + "::" + component + "<" + pstr + ">";
}

QString URI::getComponent() {
    return m_component;
}

QString URI::getName(QString name) {
    return name.split("<")[0];
}

QString URI::getComponentParams(QString uri) {
    QStringList parts = uri.split("::");
    if (parts.length() == 1) {
        return parts[0].split("<")[1].split(">")[0];
    }
    else {
        return parts[1].split("<")[1].split(">")[0];
    }
}

QString URI::getTransport() {
    return m_transport;
}

QString URI::getTransportWAddr() {
    return m_transport + "<" + m_address +">";
}

QString URI::getParam(QString data) {
    if (data.contains("<") && data.contains(">"))
        return data.split("<")[1].split(">")[0];
    else
        return QString("");
}

QString URI::getAddress() {
    return m_address;
}

QString URI::getInstance() {
    return m_component_instance;
}

QString URI::normalizeAddress(QString addr) {
    QString nAddr;
    if (addr.length() == 0) {
        nAddr = QString("Local<*>");
    }
    else if (addr == "*") {
        nAddr = QString("*");
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
            nAddr = addr.split("<")[0] + "<" + tAddr + ">";
        }
        else {
            // нормализуем
            nAddr = addr + "<*>";
        }
    }
    return nAddr;
}

QString URI::normalizeComponentName(QString cName) {
    QString nName;
    if (cName.length() == 0) {
        nName = QString("Local<*>");
    }
    else if (cName == "*") {
        nName = QString("*");
    }
    else {
        if (cName.contains("<") && cName.contains(">")) {
            nName = cName;
        }
        else {
            // нормализуем
            nName = cName + "<*>";
        }
    }
    return nName;
}
