#ifndef TRANSPORTLOCAL_H
#define TRANSPORTLOCAL_H

#include <QObject>
#include "plugininterface.h"
#include "itransport.h"

class TransportLocal : public ITransport, public PluginInterface  {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Kashier.Transport.Local")
    Q_INTERFACES(PluginInterface)
public:
    explicit TransportLocal(QObject *parent = 0);
    QString getName();
    QString getAddress();

signals:

public slots:
};

#endif // TRANSPORTLOCAL_H
