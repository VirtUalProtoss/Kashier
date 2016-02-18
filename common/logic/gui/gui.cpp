#include "gui.h"


GUI::GUI(QObject *parent) : ILogic(parent) {

}

QString GUI::getName() {
    return QString("GUI");
}

