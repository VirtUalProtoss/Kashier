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
        return URI::normalizeComponentName(parts[0]);
    }
    else if (parts.length() == 2) {
        return URI::normalizeComponentName(parts[1]);
    }
    else if (parts.length() == 3) {
        return URI::normalizeComponentName(parts[2]);
    }
    else {
        return URI::normalizeComponentName(parts[0]);
    }
}

QString URI::getName(QString uri) {
    return uri.split("<")[0];
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
    QString tr = "";
    switch (parts.length()) {
        case 1:
            if (parts[0] == "*")
                tr = parts[0];
            else
                tr = QString("Local<*>");
            break;
        case 2:
            tr = parts[1];
            break;
        case 3:
            tr = parts[1];
            break;
        default:
            break;
    }

    return tr;
}

QString URI::getParam(QString data) {
    if (data.contains("<") && data.contains(">"))
        return data.split("<")[1].split(">")[0];
    else
        return QString("");
}

QString URI::getTransportAddress(QString uri) {
    QStringList parts = uri.split("::");
    QString addr = "*";
    if (parts.length() == 3) {
        addr = getParam(normalizeComponentName(parts[0]));

    }
    return addr;
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
