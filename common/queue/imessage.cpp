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
    return m_type->toString() + "<" + m_target + ">:" + getText();
}
