#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QVariant>

#include "imessage.h"


class Query : public IMessage {
public:
    Query();
    Query(IMessage* message) : IMessage(message) {}
    Query(QString command, QMap<QString, QVariant> &params);
    bool needResponce() { return true; }
};

#endif // QUERY_H
