#include "ilogic.h"

ILogic::ILogic(QObject *parent) : QObject(parent) {

}

QString ILogic::getName() {
    return name;
}

void ILogic::setName(QString &name) {
    name = name;
}

bool ILogic::isPublic() {
    if (name != "Local")
        return true;
    else
        return false;
}

void ILogic::emit_message(IMessage *msg) {
    emit message(msg);
}

