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

    QTimer render_timer;

    unsigned long long render_count = 0;

    FpsMonitor fps_monitor{ 500ms };

};

