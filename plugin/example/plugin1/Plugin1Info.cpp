#include "Plugin1.h"

#define __IMPL__PLUGIN__
#define PLUGIN_NAME Plugin1
#define PLUGIN_INTERFACES ((IPrint,PrintHello))((IPrint,PrintWorld))
#include "ExamplePlugin.h"

