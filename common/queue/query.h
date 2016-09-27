#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QVariant>

#include "imessage.h"


class Query : public IMessage {
public:
    Query();
    Query(IMessage* message);
    Query(IMessage &message);
    Query(QString command, QMap<QString, QVariant> &params);
    bool needResponce() { return true; }
    QString getHash();
    inline QString getCommand() { return m_command; }
    QMap<QString, QVariant> getParams() { return m_params; }

    void processParams(QString params);
private:
    QMap<QString, QVariant> m_params;
    QString m_command = QString("");
};

#endif // QUERY_H
