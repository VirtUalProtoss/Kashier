#ifndef LOCAL_H
#define LOCAL_H


#include "../ilogic.h"


class Local : public ILogic {
public:
    Local(QObject *parent);
    QString getName();
};

#endif // LOCAL_H
