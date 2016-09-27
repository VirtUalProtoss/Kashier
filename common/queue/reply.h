#ifndef REPLY_H
#define REPLY_H

#include "imessage.h"

class Query;

class Reply : public IMessage {
public:
    Reply();
    Reply(Query *query);
};

#endif // REPLY_H
