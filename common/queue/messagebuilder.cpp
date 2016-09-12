#include "messagebuilder.h"

MessageBuilder::MessageBuilder(QObject *parent) : QObject(parent) {
    message = new IMessage(this);
}

void MessageBuilder::setType(QString type) {
    IMessageType* mType;
    if (type == "Query")
        mType = new IMessageType(this, type);
    else
        mType = new IMessageType();
    message->setType(mType);
}

void MessageBuilder::setSender(QString sender) {
    message->setSender(sender);
}

void MessageBuilder::setText(QString text)
{
    message->setText(text);
}

IMessage* MessageBuilder::getMessage(QString target, QString command, QMap<QString, QVariant> params) {
    //setType(QString("Query") + "<" + target + ">");
    message->setTarget(target);
    IMessageBody* body = new IMessageBody(this);
    message->setBody(body);
    QString text;
    foreach (QString key, params.keys()) {
        text += key + "==" + params.value(key).toString() + ";";
    }

    message->setText(command + "::" + text);
    return message;
}
