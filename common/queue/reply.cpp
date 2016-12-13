#include "reply.h"
#include "imessagetype.h"
#include "query.h"

Reply::Reply() {
    m_name = QString("Reply");
}

Reply::Reply(Query *query) {
    m_name = QString("Reply");
    setSender(query->getTarget());
    QMap<QString, QVariant> params = query->getParams();
    setTarget(query->getSender());
    QString text;
    foreach (QString key, params.keys()) {
        text += key + "==" + params.value(key).toString() + ";";
    }
    setText(text);
    setHash(query->getHash());
    IMessageType *mType = new IMessageType("Reply");
    setType(mType);
}

QString Reply::getSubscribe() {
    QString sub;
    sub = m_target.toString() + ";" + m_sender.toString() + ";" + getName() + "<" + m_hash + ">" + ";" + m_type->toString();
    return sub;
}
