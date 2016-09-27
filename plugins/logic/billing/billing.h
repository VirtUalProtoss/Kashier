#ifndef BILLING_H
#define BILLING_H

#include <QObject>

#include "ilogic.h"
#include "plugininterface.h"
#include "onyma/onyma.h"

class Billing : public ILogic, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Kashier.Logic.Billing")
    Q_INTERFACES(PluginInterface)
public:
    explicit Billing(QObject *parent = 0);
    void receive(IMessage *);
    QString getName();
public slots:
    void on_init_complete();
private:
    Onyma* m_onyma;
};

#endif // BILLING_H
