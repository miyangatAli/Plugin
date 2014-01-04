#include <boost/filesystem.hpp>
#ifdef _WIN32
#else
#include <dlfcn.h>
#endif
namespace fs = boost::filesystem;

template<typename IfVec>
typename PluginManagerImpl<IfVec>::GetHandle* PluginManagerImpl<IfVec>::GetHandleFun(const std::string fileName)
{
    if(!(fs::exists(fileName) && fs::is_regular_file(fileName)))
    {
	//TODO:
    }
#ifdef _WIN32
#else
    void* handle = dlopen(fileName.c_str(),RTLD_LAZY);
    if(nullptr != handle)
    {
	void* func = dlsym(handle,"GetHandle");
	return (GetHandle*)(func);
    }
    else
    {
	std::cerr<<dlerror()<<std::endl;
    }
#endif
}

template<typename IfVec>
void PluginManagerImpl<IfVec>::Load(const std::string& fileName)
{
    auto getter = GetHandleFun(fileName);
    if(nullptr != getter)
    {
        this->Merge(&getter());   
    }
}

template<typename IfVec>
void PluginManagerImpl<IfVec>::UnLoad(const std::string& fileName)
{
    auto getter = GetHandleFun(fileName);
    if(nullptr != getter)
    {
        this->Exclude(&getter());   
    }
}
