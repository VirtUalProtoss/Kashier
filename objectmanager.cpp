#include "objectmanager.h"

ObjectManager::ObjectManager(QObject *parent) : QObject(parent)
{

}

void ObjectManager::sendCommand(QString *receiver, QMap<QString, QVariant> *data, QObject *slot)
{

}

