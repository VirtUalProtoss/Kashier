#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QVariant>

#include "imessage.h"


class Query : public IMessage {
public:
    Query();
    Query(QString command, QMap<QString, QVariant> &params);
};

#endif // QUERY_H
