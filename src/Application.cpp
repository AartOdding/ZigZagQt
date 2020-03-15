#include "Application.hpp"

#include "core/systems/LibrarySystem.hpp"
#include "core/systems/NetworkSystem.hpp"
#include "core/systems/WindowSystem.hpp"

#include <QTimer>


Application::Application(int &argc, char **argv)
    : QGuiApplication(argc, argv)
{
    QTimer::singleShot(0, this, &Application::onStartup);
    connect(this, &QCoreApplication::aboutToQuit, this, &Application::onShutdown);
}


void Application::onStartup()
{
    librarySystem.load();
    networkSystem.load();
    windowSystem.load();
}


void Application::onShutdown()
{
    windowSystem.unload();
    networkSystem.unload();
}
