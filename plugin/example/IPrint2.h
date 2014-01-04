#ifndef _IPRINT2_H
#define _IPRINT2_H
#include <boost/smart_ptr.hpp>
class IPrint2
{
public:
    typedef boost::shared_ptr<IPrint2> Ptr;
    virtual ~IPrint2( void ) {}
    virtual void print2(const std::string& text) = 0;
};
#endif
 
