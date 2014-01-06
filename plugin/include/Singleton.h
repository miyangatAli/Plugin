#ifndef _SINGLETON_H
#define _SINGLETON_H
#include <boost/noncopyable.hpp>
#include <boost/thread/once.hpp>

template<typename T>
class Singleton:boost::noncopyable
{
public:
    static T& Instance( void )
    {
        static boost::once_flag init_instance = BOOST_ONCE_INIT;
        boost::call_once(init_instance,&Singleton::CreateInstance);

        return *gpInstance;
    }

private:
    static void CreateInstance( void )
    {
        gpInstance = new T();
    }

    static T* gpInstance;
};

template<typename T>
T* Singleton<T>::gpInstance = nullptr;
#endif

