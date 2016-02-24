#ifndef OPENMN_H
#define OPENMN_H

#include <QObject>

#include "../ilogic.h"


class OpenMN : public ILogic {
    Q_OBJECT
public:
    explicit OpenMN(QObject *parent = 0);

public slots:
};

#endif // OPENMN_H
