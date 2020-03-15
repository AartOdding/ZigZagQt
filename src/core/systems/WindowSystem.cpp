#include "WindowSystem.hpp"
#include "LibrarySystem.hpp"
#include "NetworkSystem.hpp"

#include <iostream>

#include <QQuickView>
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
    QQuickView* window = new QQuickView();
    window->rootContext()->setContextProperty("operatorLibrary", &librarySystem);
    window->rootContext()->setContextProperty("availableOperatorPackages", librarySystem.getAvailablePackageNames());
    window->setSource(QUrl("qrc:/NetworkView.qml"));
    window->setWidth(800);
    window->setHeight(600);
    window->show();

    std::cout << "loading window system" << std::endl;
}


void WindowSystem::unloadSystem()
{
    std::cout << "unloading window system" << std::endl;
}
