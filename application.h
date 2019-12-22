#pragma once

#include <memory>
#include <QApplication>

#include "renderer.h"
#include "view/viewport.h"
#include "view/ProjectScopeView.h"
#include "model/clock.h"


//class Clock;
class Renderer;
class Application;
class ProjectModel;
class ProjectScopeView;
class NameManager;

class QMainWindow;
class QOpenGLContext;



namespace application
{
    Application *      instance();
    Clock *            clock();
    Renderer*          renderer();
    NameManager *      name_manager();
    ProjectModel *     project_model();
    ProjectScopeView * project_view_model();
    QOpenGLContext *   main_opengl_context();
}



class Application : public QApplication
{
    Q_OBJECT

public:

    Application(int &argc, char **argv);

    NameManager *      get_name_manager();
    Clock *            get_clock();
    Renderer*          get_renderer();
    ProjectModel *     get_project_model();
    ProjectScopeView * get_project_view_model();
    QOpenGLContext *   get_main_opengl_context();


private:

    std::unique_ptr<Clock>            clock;
    std::unique_ptr<Renderer>         renderer;
    std::unique_ptr<ProjectModel>     project_model;
    std::unique_ptr<ProjectScopeView> project_view_model;

    std::unique_ptr<Viewport> viewport;
    QOpenGLWidget * main_opengl_widget;

    std::unique_ptr<QWidget> main_window;
};
