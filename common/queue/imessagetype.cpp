#include "imessagetype.h"

IMessageType::IMessageType(QObject *parent, QString type) : QObject(parent), m_type(type) {

}

void IMessageType::fromString(QString type) {
    m_type = type;
}

QString IMessageType::toString() {
    return m_type;
}
