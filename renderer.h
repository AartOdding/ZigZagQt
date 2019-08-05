#pragma once

#include <QTimer>
#include <QObject>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QOpenGLFunctions_3_2_Core>

class ProjectModel;



class Renderer : public QObject,
                 protected QOpenGLFunctions_3_2_Core
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
    QOpenGLContext context;
    QOffscreenSurface render_surface;

    QTimer render_timer;

    unsigned long long render_count = 0;

};

