#include <memory>

#include <QThread>
#include <QApplication>

#include "ui_mainwindow.h"

#include "renderer.h"
#include "view/viewport.h"
#include "view/programview.h"
#include "model/operator/operatorlibrary.h"


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
    ProgramModel model{ library };
    Renderer renderer;
    renderer.set_model(&model);

    ProgramView view;
    view.set_model(&model);

    Viewport viewport;

    viewport.set_view(&view);
    viewport.show();


    return app.exec();
}
