#include "application.h"

#include "model/projectmodel.h"
#include "model/librarymodel.h"
#include "view/projectscopeview.h"

#include "library/standard/testoperator.h"

#include <QStyle>
#include <QStyleFactory>
#include <QSurfaceFormat>

#include <QBoxLayout>
#include <QMenuBar>
#include <QMenu>


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

    LibraryModel * library_model()
    {
        return instance()->get_library_model();
    }

    ProjectScopeView * project_view_model()
    {
        return instance()->get_project_view_model();
    }
}



Application::Application(int &argc, char **argv)
    : QApplication (argc, argv)
{
    library_model = std::make_unique<LibraryModel>();
    library_model->add_operator_type("test", &create_test_operator);

    project_model = std::make_unique<ProjectModel>(*library_model);

    project_view_model = std::make_unique<ProjectScopeView>();
    project_view_model->set_model(project_model.get());

    //gl_widget = ;
    //gl_widget->setGeometry(100, 100, 1000, 720);
    //viewport.setParent(&gl_widget);
    //auto gl = new QOpenGLWidget();

    viewport = std::make_unique<Viewport>(new QOpenGLWidget());
    //viewport->

    viewport->set_view(project_view_model.get());


    QMenuBar* menu_bar = new QMenuBar(nullptr);

    QMenu* file_menu = new QMenu("File");
    QMenu* edit_menu = new QMenu("Edit");
    QMenu* view_menu = new QMenu("View");

    file_menu->addAction("Save");
    file_menu->addAction("Save As");

    edit_menu->addAction("Cut");
    edit_menu->addAction("Copy");
    edit_menu->addAction("Paste");

    view_menu->addAction("Recentre");
    view_menu->addAction("Zoom In");
    view_menu->addAction("Zoom Out");

    menu_bar->addAction(file_menu->menuAction());
    menu_bar->addAction(edit_menu->menuAction());
    menu_bar->addAction(view_menu->menuAction());

    viewport->show();

    auto layout = new QBoxLayout(QBoxLayout::TopToBottom);
    main_window = std::make_unique<QWidget>();
    main_window->setLayout(layout);

    //layout->setMenuBar();
    //viewport->show();
    //gl_widget.show();

    //std::cout << gl->width() << "\n";
    QWidget q;
    QBoxLayout l(QBoxLayout::TopToBottom);
    //.setM

}


NameManager * Application::get_name_manager()
{
    return nullptr;
}


ProjectModel * Application::get_project_model()
{
    return project_model.get();
}


LibraryModel * Application::get_library_model()
{
    return library_model.get();
}


ProjectScopeView * Application::get_project_view_model()
{
    return project_view_model.get();
}
