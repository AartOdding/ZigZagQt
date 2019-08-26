#include "application.h"
#include "renderer.h"

#include "model/projectmodel.h"
#include "model/librarymodel.h"
#include "view/projectscopeview.h"

#include "library/standard/test/testoperator.h"
#include "library/standard/test/testdataview.h"
#include "library/standard/texture/blendoperator.h"
#include "library/standard/texture/coloroperator.h"
#include "library/standard/texture/texturedataview.h"

#include <QStyle>
#include <QStyleFactory>
#include <QFontDatabase>
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

    Renderer * renderer()
    {
        return instance()->get_renderer();
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

    QOpenGLContext * main_opengl_context()
    {
        return instance()->get_main_opengl_context();
    }
}



Application::Application(int &argc, char **argv)
    : QApplication (argc, argv)
{
    int oxygen = QFontDatabase::addApplicationFont(":/fonts/OxygenMono-Regular.ttf");
    int open_sans_reg = QFontDatabase::addApplicationFont(":/fonts/OpenSans-Regular.ttf");
    int open_sans_semi = QFontDatabase::addApplicationFont(":/fonts/OpenSans-SemiBold.ttf");
    int montserrat = QFontDatabase::addApplicationFont(":/fonts/Montserrat-Regular.ttf");

    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");

    std::cout << oxygen << '\t' << open_sans_reg << '\t' << open_sans_semi << '\t' << montserrat << '\n';

    std::cout << QFontDatabase::applicationFontFamilies(oxygen).at(0).toStdString() << "\n";
    std::cout << QFontDatabase::applicationFontFamilies(open_sans_reg).at(0).toStdString() << "\n";
    std::cout << QFontDatabase::applicationFontFamilies(open_sans_semi).at(0).toStdString() << "\n";
    std::cout << QFontDatabase::applicationFontFamilies(montserrat).at(0).toStdString() << "\n";

    library_model = std::make_unique<LibraryModel>();

    library_model->register_data_type(TestData::Type);
    library_model->register_data_type(TextureData::Type);

    library_model->register_operator(TestOperator::Type);
    library_model->register_operator(BlendOperator::Type);
    library_model->register_operator(ColorOperator::Type);

    library_model->register_data_view(TestDataView::Type);
    library_model->register_data_view(TextureDataView::Type);

    // greenish color: { 205, 255, 0 }

    project_model = std::make_unique<ProjectModel>(*library_model);

    project_view_model = std::make_unique<ProjectScopeView>();
    project_view_model->set_model(project_model.get());


    //gl_widget = ;
    //gl_widget->setGeometry(100, 100, 1000, 720);
    //viewport.setParent(&gl_widget);
    //auto gl = new QOpenGLWidget();

    main_opengl_widget = new QOpenGLWidget();
    viewport = std::make_unique<Viewport>(main_opengl_widget);
    //viewport->

    viewport->set_view(project_view_model.get());

    renderer = std::make_unique<Renderer>();
    renderer->set_model(project_model.get());
    std::cout << "renderer" << renderer << "\n";

    QMenuBar* menu_bar = new QMenuBar(viewport.get());

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

}


NameManager * Application::get_name_manager()
{
    return nullptr;
}


Renderer * Application::get_renderer()
{
    return renderer.get();
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


QOpenGLContext * Application::get_main_opengl_context()
{
    // TODO: maybe change to static cast later
    return main_opengl_widget->context();
}
