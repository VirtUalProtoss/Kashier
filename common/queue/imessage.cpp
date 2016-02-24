#include "imessage.h"

IMessage::IMessage(QObject *parent) : QObject(parent) {

}

QString IMessage::getName() {
    return QString("IMessage");
}

void IMessage::setType(IMessageType *type) {
    m_type = type;
}

void IMessage::setBody(IMessageBody *body) {
    m_body = body;
}

void IMessage::setSender(QString sender) {
    m_sender = sender;
}

void IMessage::setTarget(QString target) {
    m_target = target;
}

void IMessage::setText(QString text) {
    m_text = text;
}

QString IMessage::getText() {
    return m_text;
}

QString IMessage::getSender() {
    return m_sender;
}

QString IMessage::getTarget() {
    return m_target;
}

QString IMessage::toString() {
    if (m_target.length() > 0)
        return m_type->toString() + "<" + m_target + ">:" + getText();
    else
        return m_type->toString() + ":" + getText();
}

void IMessage::fromString(QString msg) {
    QStringList items = msg.split(":");
    IMessageType *type = new IMessageType(this);
    if (items.length() > 1) {
        setText(items[1]);
        QStringList tItems = items[0].split("<");
        type->fromString(tItems[0]);
        if (tItems.length() > 1) {
            m_target = tItems[1].split(">")[0];
        }
        m_text = items[1];
    }
    else {
        type->fromString(QString("Message"));
        m_text = items[0];
    }
    m_type = type;
}
