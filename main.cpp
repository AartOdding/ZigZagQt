#include "application.h"


int main(int argc, char *argv[])
{
    //QMainWindow *widget = new QMainWindow;
    //Ui::MainWindow mw;
    //mw.setupUi(widget);
    //widget->show();

    Application app(argc, argv);
    return app.exec();
}
