#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>

#include "../common/logic/ilogic.h"
#include "../common/logic/billing/onyma/onyma.h"
#include "../common/logic/ats/openmn.h"
#include "../common/logic/local/local.h"


class Service : public QObject {
    Q_OBJECT
public:
    explicit Service(QObject *parent = 0);

signals:

public slots:
};

#endif // SERVICE_H
