#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>

class ObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = 0);
    void sendCommand(QString *receiver, QMap<QString, QVariant> *data, QObject *slot);
signals:

public slots:
};

#endif // OBJECTMANAGER_H
