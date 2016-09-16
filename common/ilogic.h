#ifndef ILOGIC_H
#define ILOGIC_H

#include <QObject>

#include "imessage.h"
#include "plugininterface.h"


class ILogic : public QObject, public PluginInterface {
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "Kashier.ILogic")
    //Q_INTERFACES(PluginInterface)
public:
    explicit ILogic(QObject *parent = 0);

    virtual QString getName();
    virtual void setName(QString name);
    virtual bool isPublic();
    virtual void receive(IMessage*);

signals:
    void message(QString);
    void message(IMessage*);

public slots:
    void emit_message(IMessage*);

private:
    QString name = "ILogic";
};

#endif // ILOGIC_H
