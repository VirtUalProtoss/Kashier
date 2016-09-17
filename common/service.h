#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include "kashiercommon_global.h"
#include "plugininterface.h"
#include <QSettings>

class QueueBroker;

class KASHIERCOMMONSHARED_EXPORT Service : public QObject {
    Q_OBJECT
public:
    explicit Service(QObject *parent = 0);

    void loadPlugins();
    PluginInterface* loadPlugin(QString fileName);
    void loadConfig(QString fileName, QString filePath="");
    void loadComponents(QSettings &sett, QString section);
signals:

private:
    QueueBroker* broker;
    QString appDir;
};

#endif // SERVICE_H
