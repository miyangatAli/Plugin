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

    std::cout<<"Remove not exists impl--HAHA:"<<PluginManager::Instance().Remove<IPrint>("HAHA")<<std::endl;
    std::cout<<"Remove not match iface--Print:"<<PluginManager::Instance().Remove<IPrint2>("PrintHello")<<std::endl;
    std::cout<<"Remove match iface--Print:"<<PluginManager::Instance().Remove<IPrint>("PrintHello")<<std::endl;
    auto shouldnull = PluginManager::Instance().Create<IPrint>("PrintHello");
    std::cout<<"Should null: "<<shouldnull.get()<<std::endl;

    std::cout<<"Exclude match"<<std::endl;
    PluginManager::Instance().UnLoad("libPlugin2.so");
    auto nullName = PluginManager::Instance().Create<IPrint>("PrintName");
    auto nullText = PluginManager::Instance().Create<IPrint2>("Print");
    std::cout<<"null Name:"<<nullName.get()<<std::endl;
    std::cout<<"null text:"<<nullText.get()<<std::endl;

    std::cout<<"PrintWorld should world"<<std::endl;
    printWorld = PluginManager::Instance().Create<IPrint>("PrintWorld");
    printWorld->print();
    return 0;
}

