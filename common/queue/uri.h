#ifndef URI_H
#define URI_H

#include <QString>
#include <QVariant>

/*
    URI format:
    [transport_name[<address:port>|<*>]{=Local<*>}::]component_name[<self_name[:{instance_id|thread_id}>]]{=<*>}

*/

class URI {

public:
    explicit URI();
    URI(QString);
    QString getURI(
            QString transport = QString("Local<*>"),
            QString component = QString("Broker<*>"),
            QMap<QString, QVariant> params = QMap<QString, QVariant>()
    );
    QString getComponent();
    static QString getComponentParams(QString uri);
    QString getTransport();
    QString getAddress();
    QString getInstance();
    inline void setAddress(QString addr) { m_address = addr; }
    inline void setTransport(QString tr) { m_transport = tr; }
    static QString normalizeAddress(QString addr);
    static QString normalizeComponentName(QString cName);
    QString getName(QString name);
    static QString getParam(QString data);
    inline QString toString() {
        QString instance = "*";
        if (m_component_instance.length() > 0)
            instance = m_component_instance;
        QString rStr = m_transport + "<" + m_address +">::" + m_component + "<" + instance +">";
        return rStr;
    }

    QString getTransportWAddr();
private:
    QString m_splitter;
    QString m_uri;
    QString m_address;
    QString m_transport;
    QString m_component;
    QString m_component_instance;
};

#endif // URI_H
