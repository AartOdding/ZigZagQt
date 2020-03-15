#include "NetworkSystem.hpp"

#include <iostream>

NetworkSystem networkSystem;


NetworkSystem::NetworkSystem()
    : BaseSystem("networkSystem")
{

}


bool NetworkSystem::canBeLoaded()
{
    return true;
}


void NetworkSystem::loadSystem()
{
    std::cout << "loading network system" << std::endl;
}


void NetworkSystem::unloadSystem()
{
    std::cout << "unloading network system" << std::endl;
}

