#include "messagebuilder.h"
#include "uri.h"

MessageBuilder::MessageBuilder(QObject *parent) : QObject(parent) {
    message = new IMessage(this);
}

void MessageBuilder::setType(QString type) {
    IMessageType* mType = new IMessageType(type);
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
    URI uTarget = URI(target);
    //uTarget.setTransport(uTarget.getName(target));
    //uTarget.setAddress(uTarget.getParam(target));
    message->setTarget(uTarget);
    IMessageBody* body = new IMessageBody(this);
    message->setBody(body);
    QString text;
    foreach (QString key, params.keys()) {
        text += key + "==" + params.value(key).toString() + ";";
    }

    message->setText(command + "::" + text);
    return message;
}
