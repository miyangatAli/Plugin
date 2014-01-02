#ifdef __IMPL__PLUGIN__
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/stringize.hpp>
//#include <boost/thread/once.hpp>

#define PLUGIN_INSTANCE BOOST_PP_CAT(BOOST_PP_CAT(gp,name),Instance)
#define PLUGIN_INIT_FUNC BOOST_PP_CAT(Init,name)
#define PLUGIN_CREATOR(ifce,impl) []()->boost::shared_ptr<ifce> { return boost::make_shared<impl>(); }
#define iface(tup) BOOST_PP_TUPLE_ELEM(2,0,tup)
#define impl(tup) BOOST_PP_TUPLE_ELEM(2,1,tup)
#define PLUGIN_REGISTER(z,d,tup) PLUGIN_INSTANCE->Add(iface(tup)::Name,BOOST_PP_STRINGIZE(impl(tup)),PLUGIN_CREATOR(iface(tup),impl(tup)));

static Plugin* PLUGIN_INSTANCE = nullptr;
void PLUGIN_INIT_FUNC( void )
{
    BOOST_PP_SEQ_FOR_EACH(PLUGIN_REGISTER,~,plugins)
}

boost::once_flag init_plugin_once = BOOST_ONCE_INIT;
Plugin* GetHandle( void )
{
    boost::call_once(PLUGIN_INIT_FUNC,init_plugin_once);
    return PLUGIN_INSTANCE;
}

#undef PLUGIN_INSTANCE 
#undef PLUGIN_INIT_FUNC
#undef PLUGIN_CREATOR
#undef iface
#undef impl
#undef PLUGIN_REGISTER

#undef name
#undef plugins
#undef __IMPL__PLUGIN__

#endif
