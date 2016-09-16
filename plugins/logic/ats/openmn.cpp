#include "openmn.h"

OpenMN::OpenMN(QObject *parent) : ILogic(parent) {

}

QString OpenMN::getName() {
    return QString("OpenMN");
}
