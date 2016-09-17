#include "plugininterface.h"

PluginInterface::PluginInterface()
{
}

PluginInterface::~PluginInterface()
{

}

ILogic* PluginInterface::getInstance(ILogic *)
{

}

ITransport* PluginInterface::getInstance(ITransport *)
{

}

QString PluginInterface::getType()
{
    return QString("PluginInterface");
}
