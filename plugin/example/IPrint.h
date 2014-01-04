#ifndef _IPRINT_H
#define _IPRINT_H
#include <boost/smart_ptr.hpp>
class IPrint
{
public:
    typedef boost::shared_ptr<IPrint> Ptr;
    virtual ~IPrint( void ) {}
    virtual void print( void ) = 0;
};
#endif
 
