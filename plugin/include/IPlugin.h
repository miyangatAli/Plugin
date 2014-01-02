#ifndef _IPLUGIN_H
#define _IPLUGIN_H
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/preprocessor/>

struct IfImplInfo
{
    IfImplInfo(const std::string& ifName,const std::string& implName)
	:IfName(ifName)
	,ImplName(implName)
    {}

    const std::string IfName;
    const std::string ImplName;
};

template<typename If,typename Impl>
struct PluginCreator
{
public:
    typename If::Ptr Create( void )
    {
	return boost::make_shared<Impl>();
    }
};

class Plugin
{
public:
    typedef std::vector<IfImplInfo> InterfaceList;
    typedef boost::shared_ptr<IPlugin> Ptr;

    virtual const InterfaceList& Interfaces( void ) { return mImplInfos;}

    template<typename If>
    typename If::Ptr Create(const std::string& name)
    {
	return If::DoCreate(PluginTag<If>,name);
    }

    template<typename If,typename Impl>
    void Add
private:
    InterfaceList mImplInfos;
};


#endif

