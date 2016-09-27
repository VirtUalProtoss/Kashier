#include "reply.h"
#include "imessagetype.h"
#include "query.h"

Reply::Reply() {
}

Reply::Reply(Query *query) {
    setSender(query->getTarget());
    QMap<QString, QVariant> params = query->getParams();
    setTarget(query->getSender());
    QString text;
    foreach (QString key, params.keys()) {
        text += key + "==" + params.value(key).toString() + ";";
    }
    setText(text);
    setHash(query->getHash());
    IMessageType *mType = new IMessageType(this, "Reply<" + getHash() + ">");
    setType(mType);
}
