#include "uri.h"

URI::URI() {

}

QString URI::getURI(QString transport, QString component, QMap<QString, QVariant> params) {
    QString pstr;
    foreach (QString param, params.keys()) {
        pstr += param + "=" + params.value(param).toString();
    }
    return transport + "::" + component + "<" + pstr + ">";
}

/*
    URI format:
    [transport_name[<address:port>|<*>]::]component_name[<self_name[:{instance_id|thread_id}>]]

*/

QString URI::getComponent(QString uri) {
    QStringList parts = uri.split("::");
    if (parts.length() == 1) {
        return parts[0].split("<")[0];
    }
    else {
        return parts[1].split("<")[0];
    }
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

QString URI::getTransport(QString uri) {
    QStringList parts = uri.split("::");
    if (parts.length() == 1) {
        return QString("Local");
    }
    else {
        return parts[0].split("<")[0];
    }
}

QString URI::getTransportAddress(QString uri) {
    QStringList parts = uri.split("::");
    if (parts.length() == 1) {
        return QString("Local");
    }
    else {
        return parts[0].split("<")[1].split(">")[0];
    }
}

QString URI::normalizeAddress(QString addr) {
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
    else {
        if (cName.contains("<") && cName.contains(">")) {
            // self-name defined
            QString selfName = cName.split("<")[1].split(">")[0];
            if (!selfName.contains(":")) {
                selfName =  selfName + ":*";
            }
            nName = cName.split("<")[0] + "<" + selfName + ">";
        }
        else {
            // нормализуем
            nName = cName + "<*>";
        }
    }
    return nName;
}
