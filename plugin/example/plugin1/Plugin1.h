#include <iostream>
#include "IPrint.h"

class PrintHello:public IPrint
{
public:
    virtual void print()
    {
	std::cout<<"Hello ";
    }
};

class PrintWorld:public IPrint
{
public:
    virtual void print()
    {
	std::cout<<"World"<<std::endl;
    }
};
