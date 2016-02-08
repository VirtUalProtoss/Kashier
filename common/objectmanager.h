#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>

#include "ktask.h"

class ObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = 0);
    void sendCommand(QString *receiver, QMap<QString, QVariant> *data, QObject *slot);

private:
    KTask *tasks[];
signals:

public slots:
};

#endif // OBJECTMANAGER_H
