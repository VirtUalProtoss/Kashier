#ifndef REPLY_H
#define REPLY_H

#include "imessage.h"

class Query;

class Reply : public IMessage {
public:
    Reply();
    Reply(Query *query);
    QString getSubscribe();
};

#endif // REPLY_H
