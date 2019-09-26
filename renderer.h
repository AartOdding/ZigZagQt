#pragma once

#include <QObject>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLWidget>


#include "utility/fpsmonitor.h"


class ProjectModel;



class Renderer : public QObject,
                 public QOpenGLFunctions_3_3_Core
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

    QOpenGLWidget opengl_widget;
    //QOffscreenSurface opengl_surface;
    //QOpenGLContext opengl_context;

    FpsMonitor fps_monitor{ 500ms };

};

