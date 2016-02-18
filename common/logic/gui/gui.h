#ifndef GUI_H
#define GUI_H

#include "../ilogic.h"


class GUI : public ILogic {
public:
    GUI(QObject *parent);
    QString getName();
};

#endif // GUI_H
