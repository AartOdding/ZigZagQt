#pragma once

#include <memory>
#include <QApplication>

#include "renderer.h"
#include "view/viewport.h"


class Renderer;
class Application;
class ProjectModel;
class ProjectScopeView;
class LibraryModel;
class NameManager;

class QMainWindow;


namespace application
{
    Application *      instance();
    Renderer*          renderer();
    NameManager *      name_manager();
    ProjectModel *     project_model();
    LibraryModel *     library_model();
    ProjectScopeView * project_view_model();
}



class Application : public QApplication
{
    Q_OBJECT

public:

    Application(int &argc, char **argv);

    NameManager *      get_name_manager();
    Renderer*          get_renderer();
    ProjectModel *     get_project_model();
    LibraryModel *     get_library_model();
    ProjectScopeView * get_project_view_model();


private:

    std::unique_ptr<Renderer>         renderer;
    std::unique_ptr<ProjectModel>     project_model;
    std::unique_ptr<LibraryModel>     library_model;
    std::unique_ptr<ProjectScopeView> project_view_model;

    std::unique_ptr<Viewport> viewport;

    std::unique_ptr<QWidget> main_window;
};
