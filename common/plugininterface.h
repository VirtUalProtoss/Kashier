#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>

class ILogic;
class ITransport;

class PluginInterface {
public:
    PluginInterface();
    virtual ~PluginInterface();
    virtual QString getType();
};
Q_DECLARE_INTERFACE(PluginInterface, "Kashier.PluginInterface")

#endif // PLUGININTERFACE_H
