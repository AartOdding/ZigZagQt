#pragma once

#include <memory>
#include <QApplication>

#include "view/viewport.h"
#include "view/parametereditor.h"


class Application;
class ProjectModel;
class ProjectScopeView;
class OperatorLibrary;
class NameManager;

#include <iostream>

namespace application
{
    Application *      instance();
    NameManager *      name_manager();
    ProjectModel *     project_model();
    OperatorLibrary *  operator_library();
    ProjectScopeView * project_view_model();
}



class Application : public QApplication
{
    Q_OBJECT

public:

    Application(int &argc, char **argv);

    NameManager *      get_name_manager();
    ProjectModel *     get_project_model();
    OperatorLibrary *  get_operator_library();
    ProjectScopeView * get_project_view_model();


private:

    //std::unique_ptr<NameManager>      name_manager;
    std::unique_ptr<ProjectModel>     project_model;
    std::unique_ptr<OperatorLibrary>  operator_library;
    std::unique_ptr<ProjectScopeView> project_view_model;

    Viewport viewport;

};
