#include "application.h"

#include "model/projectmodel.h"
#include "model/operatorlibrary.h"
#include "view/projectscopeview.h"

#include "library/standard/testoperator.h"

#include <QStyle>
#include <QStyleFactory>
#include <QSurfaceFormat>



namespace application
{
    Application * instance()
    {
        return qobject_cast<Application *>(QApplication::instance());
    }

    NameManager * name_manager()
    {
        return instance()->get_name_manager();
    }

    ProjectModel * project_model()
    {
        return instance()->get_project_model();
    }

    OperatorLibrary * operator_library()
    {
        return instance()->get_operator_library();
    }

    ProjectScopeView * project_view_model()
    {
        return instance()->get_project_view_model();
    }
}


Application::Application(int &argc, char **argv)
    : QApplication (argc, argv)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(1);
    QSurfaceFormat::setDefaultFormat(format);

    operator_library = std::make_unique<OperatorLibrary>();
    operator_library->add_operator_type("test", &create_test_operator);

    project_model = std::make_unique<ProjectModel>(*operator_library);

    project_view_model = std::make_unique<ProjectScopeView>();
    project_view_model->set_model(project_model.get());

    viewport.set_view(project_view_model.get());
    viewport.show();
}


NameManager * Application::get_name_manager()
{
    return nullptr;
}


ProjectModel * Application::get_project_model()
{
    return project_model.get();
}


OperatorLibrary * Application::get_operator_library()
{
    return operator_library.get();
}


ProjectScopeView * Application::get_project_view_model()
{
    return project_view_model.get();
}
