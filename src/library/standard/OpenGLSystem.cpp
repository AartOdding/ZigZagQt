#include "OpenGLSystem.hpp"
#include "core/systems/LibrarySystem.hpp"

#include <iostream>

OpenGLSystem openGLSystem;



OpenGLSystem::OpenGLSystem()
    : BaseSystem("openGLSystem")
{

}


bool OpenGLSystem::canBeLoaded()
{
    return librarySystem.isLoaded();
}


void OpenGLSystem::loadSystem()
{
    std::cout << "loading opengl system" << std::endl;
}


void OpenGLSystem::unloadSystem()
{
    std::cout << "unloading opengl system" << std::endl;
}
