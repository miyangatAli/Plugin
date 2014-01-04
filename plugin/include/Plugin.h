#ifndef _IPLUGIN_H
#define _IPLUGIN_H
#include <vector>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/unordered/unordered_map.hpp>

template<typename If>
struct PluginIfTag
{
    typedef boost::shared_ptr<If> Ptr;
    typedef boost::function<Ptr ( void )> Creator;
    typedef boost::unordered_map<std::string,Creator> CreatorMap;
};

struct EmptyCreator
{
    typedef PluginIfTag<EmptyCreator> Tag;
    void DoCreate()const;
    void DoAdd()const;
    void DoRemove()const;
    void DoGetIfCreatorMap()const;
    void DoMerge(Tag,const void*)const{}
    void DoExclude(Tag,const void*)const{}
};

template<typename If,typename More>
struct PluginIfCreator:public More
{
public:
    typedef More Base;
    typedef PluginIfTag<If> Tag;
    typedef typename Tag::Ptr Ptr;
    typedef typename Tag::Creator Creator;
    typedef typename Tag::CreatorMap CreatorMap;

    Ptr DoCreate(Tag /*tag*/,const std::string& name)
    {
	auto itCreator = mCreatores.find(name);
	if(mCreatores.end() != itCreator)
	{
	    return itCreator->second();
	}
	return nullptr;
    }

    bool DoAdd(Tag /*tag*/,const std::string& name,Creator creator)
    {
	auto result = mCreatores.insert(std::make_pair(name,creator));
	return result.second;
    }

    bool DoRemove(Tag /*tag*/,const std::string& name)
    {
        return 1 == mCreatores.erase(name);
    }

    const CreatorMap& DoGetIfCreatorMap(Tag /*tag*/) const { return mCreatores;}

    void DoMerge(Tag tag,const PluginIfCreator* plugins)
    {
        mCreatores.insert(plugins->DoGetIfCreatorMap(tag).begin(),plugins->DoGetIfCreatorMap(tag).end());
	DoMerge(typename More::Tag(),plugins);
    }

    void DoExclude(Tag tag,const PluginIfCreator* plugins)
    {
	mCreatores.erase(plugins->DoGetIfCreatorMap(tag).begin(),plugins->DoGetIfCreatorMap(tag).end());
	DoExclude(typename More::Tag(),plugins);
    }

    using Base::DoCreate;
    using Base::DoAdd;
    using Base::DoRemove;
    using Base::DoGetIfCreatorMap;
    using Base::DoMerge;
    using Base::DoExclude;
private:
    CreatorMap mCreatores;
};

template<typename IfVec>
struct PluginImpl:public boost::mpl::inherit_linearly<IfVec,PluginIfCreator<boost::mpl::_2,boost::mpl::_1>,EmptyCreator >::type
{
    template<typename If>
    typename PluginIfTag<If>::Ptr Create(const std::string& name)
    {
	return this->DoCreate(PluginIfTag<If>(),name);
    }

    template<typename If>
    bool Add(const std::string& name,typename PluginIfTag<If>::Creator creator)
    {
	return this->DoAdd(PluginIfTag<If>(),name,creator);
    }

    template<typename If>
    bool Remove(const std::string& name)
    {
	return this->DoRemove(PluginIfTag<If>(),name);
    }

    template<typename If>
    const typename PluginIfTag<If>::CreatorMap& GetCreatorMap( void ) const
    {
	return this->DoGetIfCreatorMap(PluginIfTag<If>());
    }

    template<typename If>
    bool SupportIf( void ) const { return boost::mpl::contains<IfVec,If>::type::value;}

    void Merge(const PluginImpl* plugin)
    {
	this->DoMerge(PluginIfTag<typename boost::mpl::back<IfVec>::type>(),plugin);
    }

    void Exclude(const PluginImpl* plugin)
    {
    	this->DoExclude(PluginIfTag<typename boost::mpl::back<IfVec>::type>(),plugin);
    }
};

#endif

