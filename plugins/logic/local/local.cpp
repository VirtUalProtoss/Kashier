#include "local.h"

Local::Local(QObject *parent) : ILogic(parent) {

}

QString Local::getName() {
    return QString("Local");
}

bool Local::isPublic() {
    return false;
}

