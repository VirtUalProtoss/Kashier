#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>

class ILogic;
class ITransport;

class PluginInterface
{
public:
    PluginInterface();
    virtual ~PluginInterface();
    virtual ILogic* getInstance(ILogic*);
    virtual ITransport* getInstance(ITransport*);
};
Q_DECLARE_INTERFACE(PluginInterface, "Kashier.PluginInterface")

#endif // PLUGININTERFACE_H
