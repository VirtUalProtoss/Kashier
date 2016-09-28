#include "imessagetype.h"

IMessageType::IMessageType(QString type) : m_type(type) {

}

void IMessageType::fromString(QString type) {
    m_type = type;
}

QString IMessageType::toString() {
    return m_type;
}
