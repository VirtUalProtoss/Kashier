#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>

class PluginInterface
{
public:
    PluginInterface();
    virtual ~PluginInterface();

};
Q_DECLARE_INTERFACE(PluginInterface, "Kashier.PluginInterface")

#endif // PLUGININTERFACE_H
