#include "ExamplePlugin.h"
#include "IPrint.h"
#include "IPrint2.h"

int main(int argc,char** argv)
{
    PluginManager::Instance().Load("libPlugin1.so"); //PrintHello:IPrint,PrintWorld:IPrint
    PluginManager::Instance().Load("libPlugin2.so"); //PrintName:IPrint,Print:IPrint2

    auto printHello = PluginManager::Instance().Create<IPrint>("PrintHello"); 
    printHello->print();

    auto printWorld = PluginManager::Instance().Create<IPrint>("PrintWorld"); 
    printWorld->print();


    auto printName = PluginManager::Instance().Create<IPrint>("PrintName");
    printName->print();

    auto print = PluginManager::Instance().Create<IPrint2>("Print");
    print->print2("all is ok");

    return 0;
}

