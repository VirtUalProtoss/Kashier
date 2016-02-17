#include "objectmanager.h"

ObjectManager::ObjectManager(QObject *parent) : QObject(parent), broker(new QueueBroker(this)) {

}


void ObjectManager::addComponent(ILogic *component) {
    qDebug() << components.size();
    components.append(component);
}

