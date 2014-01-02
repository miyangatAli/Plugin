#ifndef __PLUGINMANAGER_H
#define __PLUGINMANAGER_H

class PluginManager: public Singleton<PluginManager>
{
public:
    void Load();

    Create(const std::string& name);
};
#endif


