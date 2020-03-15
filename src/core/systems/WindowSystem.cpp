#include "WindowSystem.hpp"
#include "LibrarySystem.hpp"
#include "NetworkSystem.hpp"

#include <iostream>

#include <QQmlContext>


WindowSystem windowSystem;


WindowSystem::WindowSystem()
    : BaseSystem("windowSystem")
{

}


bool WindowSystem::canBeLoaded()
{
    return librarySystem.isLoaded() && networkSystem.isLoaded();
}


void WindowSystem::loadSystem()
{
    m_window = std::make_unique<QQuickView>();
    m_window->rootContext()->setContextProperty("operatorLibrary", &librarySystem);
    m_window->rootContext()->setContextProperty("availableOperatorPackages", librarySystem.getAvailablePackageNames());
    m_window->setSource(QUrl("qrc:/NetworkView.qml"));
    m_window->setWidth(800);
    m_window->setHeight(600);
    m_window->show();

    std::cout << "loading window system" << std::endl;
}


void WindowSystem::unloadSystem()
{
    m_window.reset(nullptr);
    std::cout << "unloading window system" << std::endl;
}
