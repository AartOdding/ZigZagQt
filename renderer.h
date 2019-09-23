#pragma once

#include <QTimer>
#include <QObject>

#include "utility/fpsmonitor.h"


class ProjectModel;



class Renderer : public QObject
{
    Q_OBJECT

public:

    Renderer();

    ~Renderer();

    void set_model(ProjectModel* model);


public slots:

    void render_frame();


private:

    ProjectModel* model;

    FpsMonitor fps_monitor{ 500ms };

};

