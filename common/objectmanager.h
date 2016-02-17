#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <QList>
#include <QDebug>


#include "queue/iqueuebroker.h"
#include "queue/queuebroker.h"
#include "logic/ilogic.h"


class ObjectManager : public QObject {
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = 0);
    void addComponent(ILogic* component);
signals:

public slots:

private:
    IQueueBroker *broker;
    QList<ILogic*> components;
};

#endif // OBJECTMANAGER_H
