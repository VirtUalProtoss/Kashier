#ifndef URI_H
#define URI_H

#include <QString>
#include <QVariant>

class URI {
    const QString m_splitter;
public:
    URI();
    static QString getURI(
            QString transport = QString("Local<*>"),
            QString component = QString("Broker<*>"),
            QMap<QString, QVariant> params = QMap<QString, QVariant>()
    );
    static QString getComponent(QString uri);
    static QString getComponentParams(QString uri);
    static QString getTransport(QString uri);
    static QString getTransportAddress(QString uri);
    static QString normalizeAddress(QString addr);
    static QString normalizeComponentName(QString cName);
    static QString getName(QString uri);
    static QString getParam(QString data);
};

#endif // URI_H
