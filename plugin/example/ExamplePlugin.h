#ifndef _EXAMPLE_PLUGIN_H
#define _EXAMPLE_PLUGIN_H
#include <boost/mpl/vector.hpp>
#include "PluginManager.h"
class IPrint;
class IPrint2;

typedef boost::mpl::vector<IPrint,IPrint2> Interfaces;
typedef PluginImpl<Interfaces> Plugin;
typedef PluginManagerImpl<Interfaces> PluginManager;

#include "PluginUtils.h"
#endif

