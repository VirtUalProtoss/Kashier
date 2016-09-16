#include "service.h"
#include "queuebroker.h"

#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>
#include "plugininterface.h"


Service::Service(QObject *parent) : QObject(parent), broker(new QueueBroker(this)) {
    //ILogic* local = new Local(this);
    //ITransport* tLocal = new TransportLocal(this);
    //broker->addComponent(local);
    //broker->addComponent(tLocal);

    //broker->addComponentMap(tLocal, local);
    qDebug() << "Init common lib";
    loadPlugins();
}

void Service::loadPlugins() {
    qDebug() << "Load plugins";
    QDir dir(QCoreApplication::applicationDirPath());
    if (false == dir.cd("../plugins")) return;
    foreach (QString fileName, dir.entryList(QDir::Files)) {
        QPluginLoader loader(dir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (nullptr == plugin) continue;
        PluginInterface *pI = qobject_cast<PluginInterface*>(plugin);
        if (nullptr == pI) continue;
        //m_ui->methods->addItem(pI->text(), (unsigned int) pI);
        broker->addComponent(pI);
    }
}
