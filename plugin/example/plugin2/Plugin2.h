#ifndef _PRINT2_H
#define _PRINT2_H
#include <iostream>
#include <string>
#include "IPrint.h"
#include "IPrint2.h"
class PrintName:public IPrint
{
public:
    virtual void print()
    {
	std::cout<<"Plugin2"<<std::endl;
    }
};

class Print:public IPrint2
{
public:
    virtual void print2(const std::string& text)
    {
	std::cout<<text<<std::endl;
    }
};
#endif
 
