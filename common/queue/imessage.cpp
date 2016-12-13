#include "imessage.h"

IMessage::IMessage(QObject *parent) : QObject(parent) {

}

IMessage::IMessage(QString msg) {
    fromString(msg);
}

void IMessage::setType(IMessageType *type) {
    m_type = type;
}

void IMessage::setBody(IMessageBody *body) {
    m_body = body;
}

void IMessage::setSender(URI sender) {
    m_sender = sender;
}

void IMessage::setTarget(URI target) {
    m_target = target;
}

void IMessage::setText(QString text) {
    m_text = text;
}

void IMessage::setHash(QString hash)
{
    m_hash = hash;
}

QString IMessage::getHash()
{
    return m_hash;
}

QString IMessage::getText() {
    return m_text;
}

QString IMessage::getType() {
    return m_type->toString();
}

URI IMessage::getSender() {
    return m_sender;
}

URI IMessage::getTarget() {
    return m_target;
}

QString IMessage::getSubscribe() {
    QString sub;
    sub = m_sender.toString() + ";" + m_target.toString() + ";" + m_type->toString();
    return sub;
}

QString IMessage::toString() {
    return m_sender.toString() + "##" + m_target.toString() + "##" + m_type->toString() + "##" + QString::number(m_protocol) + "##" + getText();
}

void IMessage::fromString(QString msg) {
    QStringList items = msg.split("##");
    IMessageType *type = new IMessageType();
    if (items.length() > 1) {
        m_sender = URI(items[0]);
        m_target = URI(items[1]);
        type->fromString(items[2]);
        m_protocol = items[3].toInt();
        m_text = items[4];
    }
    else {
        type->fromString(QString("Message"));
        m_text = items[1];
    }
    m_type = type;
}
