#pragma once

#include <QGuiApplication>



class Application : public QGuiApplication
{

public:

    Application(int &argc, char **argv);

public slots:

    void onStartup();

    void onShutdown();


};

