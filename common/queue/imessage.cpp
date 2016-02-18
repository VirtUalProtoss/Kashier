#include "imessage.h"

IMessage::IMessage(QObject *parent) : QObject(parent) {

}

QString IMessage::getName() {
    return QString("IMessage");
}

