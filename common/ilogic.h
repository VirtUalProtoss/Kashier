#ifndef ILOGIC_H
#define ILOGIC_H

#include <QObject>
#include <QDebug>

#include "imessage.h"
#include "plugininterface.h"


class ILogic : public QObject, public PluginInterface {
    Q_OBJECT

public:
    explicit ILogic(QObject *parent);
    virtual QString getName();
    virtual void setName(QString &name);
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
