#ifndef __PLUGINMANAGER_H
#define __PLUGINMANAGER_H
#include "Plugin.h"
#include "Singleton.h"
template<typename IfVec>
class PluginManagerImpl: public Singleton<PluginManagerImpl<IfVec> >
		   , public PluginImpl<IfVec>
{
public:
    typedef PluginImpl<IfVec>& GetHandle( void );
    void Load(const std::string& fileName);
    void UnLoad(const std::string& fileName);

private:
    GetHandle* GetHandleFun(const std::string ileName);
};

#include "PluginManager.hpp"
#endif


