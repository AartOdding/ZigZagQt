#include <memory>

#include <QThread>
#include <QApplication>

#include "ui_mainwindow.h"

#include "renderer.h"

#include "view/viewport.h"
#include "view/programview.h"

#include "model/operatorlibrary.h"

#include "library/standard/testoperator.h"


static ProgramModel * main_model;
static OperatorLibrary * main_library;


ProgramModel * get_main_model()
{
    return main_model;
}

OperatorLibrary * get_main_library()
{
    return main_library;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(1);
    QSurfaceFormat::setDefaultFormat(format);



    //QMainWindow *widget = new QMainWindow;
    //Ui::MainWindow mw;
    //mw.setupUi(widget);
    //widget->show();

    // -----------------

    OperatorLibrary library;
    library.add_operator_type("test", &create_test_operator);


    ProgramModel model{ library };

    main_model = &model;
    main_library = &library;

    Renderer renderer;
    renderer.set_model(&model);

    ProgramView view;
    view.set_model(&model);

    Viewport viewport;

    viewport.set_view(&view);
    viewport.show();


    return app.exec();
}
