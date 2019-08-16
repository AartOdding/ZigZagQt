#include "application.h"


int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(1);
    format.setSamples(8);

    QSurfaceFormat::setDefaultFormat(format);

    //QMainWindow *widget = new QMainWindow;
    //Ui::MainWindow mw;
    //mw.setupUi(widget);
    //widget->show();

    Application app(argc, argv);
    return app.exec();
}
