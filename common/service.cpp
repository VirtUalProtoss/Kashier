#include "service.h"
#include "queuebroker.h"

#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>



Service::Service(QObject *parent) : QObject(parent), broker(new QueueBroker(this)) {
    qDebug() << "Init common lib";
    appDir = QCoreApplication::applicationDirPath();
    //loadPlugins();
}

PluginInterface* Service::loadPlugin(QString fileName) {
    qDebug() << "Load plugin" << fileName;
    bool loaded = false;
    QDir dir;
    QPluginLoader loader(dir.absoluteFilePath(fileName));
    QObject *plugin = loader.instance();
    if (nullptr == plugin) {
        qDebug() << "Skip non-plugin library";
        qDebug() << loader.isLoaded();
        qDebug() << loader.errorString();
        return (PluginInterface *)loaded;
    }
    PluginInterface *pI = qobject_cast<PluginInterface*>(plugin);
    if (nullptr == pI) {
        qDebug() << "Skip alien plugin";
        return (PluginInterface *)loaded;
    }
    //loaded = true;
    //broker->addComponent(pI, params);
    return pI;
}

void Service::loadPlugins() {
    qDebug() << "Load plugins";
    QDir dir(appDir);
    if (false == dir.cd("plugins")) {
        qDebug() << "Plugins dir not found";
        return;
    }

    foreach (QString fileName, dir.entryList(QDir::Files)) {
        //loadPlugin(fileName);
    }
}

QMap<QString, QVariant> getSectionValues(QSettings &sett, QString section) {
    QMap<QString, QVariant> data;
    QStringList sections = sett.childGroups();
    if (sections.contains(section)) {
        sett.beginGroup(section);
            foreach (QString key, sett.childKeys()) {
                data[key] = sett.value(key);
            }
        sett.endGroup();
    }
    return data;
}

QString getDLLFullName(QString dllName) {
#ifdef QT_DEBUG
    QString dllFullName = QString("lib") + dllName + QString("d.so");
#else
    QString dllFullName = QString("lib") + data["dll"].toString() + QString(".so");
#endif
    return dllFullName;
}

void Service::loadComponents(QSettings &sett, QString section) {
    QMap<QString, QVariant> sections = getSectionValues(sett, section);
    QDir dir;
    QString pluginDir = appDir + dir.separator() + QString("plugins");
    foreach (QString key, sections.keys()) {
        QMap<QString, QVariant> data = getSectionValues(sett, sections[key].toString());
        if (data.contains("dll")) {
            QString dllName = getDLLFullName(data["dll"].toString());
            PluginInterface* pluginDLL = loadPlugin(pluginDir + dir.separator() + dllName);
            if (pluginDLL) {
                broker->addComponent(pluginDLL, data);
            }
        }
    }
}

void Service::loadConfig(QString fileName, QString filePath) {
    QDir dir;
    QString configPath;
    if (filePath.length() == 0) {
        configPath = appDir + dir.separator() + QString("..") \
                + dir.separator() + QString("etc");
    }
    else {
        configPath = filePath;
    }

    QSettings sett(configPath + dir.separator() + fileName, QSettings::IniFormat);
    loadComponents(sett, "transports");
    loadComponents(sett, "components");

    //QMap<QString, QVariant> maps;
    QMap<QString, QVariant> subscribes = getSectionValues(sett, "subscribes");
    foreach (QString key, subscribes.keys()) {
        QString value = subscribes[key].toString();
        broker->addSubscribe(value);
    }

}
