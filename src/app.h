//#pragma once

//#include <memory>
//#include <QApplication>
//#include <QThread>

//#include "renderer.h"
//#include "view/Viewport.hpp"
//#include "view/OperatorNetworkView.hpp"
//#include "view/parameter/parametereditor.h"
//#include "model/clock.h"


//class Renderer;
//class Application;
//class OperatorNetwork;
//class OperatorNetworkView;
//class ParameterEditor;
//class ExecutionEngine;
//class ExecutionEngineWindow;

//class QMainWindow;
//class QOpenGLContext;



//namespace application
//{
//    Application *      instance();
//    Clock *            clock();
//    //Renderer*          renderer();
//    OperatorNetwork *     project_model();
//    OperatorNetworkView * project_view_model();
//    ParameterEditor* parameterEditor();

//    //QOpenGLContext *   main_opengl_context();
//}



//class Application : public QApplication
//{
//    Q_OBJECT

//public:

//    Application(int &argc, char **argv);

//    Clock *            get_clock();
//    //Renderer*          get_renderer();
//    OperatorNetwork *     get_project_model();
//    OperatorNetworkView * get_project_view_model();
//    //QOpenGLContext *   get_main_opengl_context();
//    ParameterEditor* getParameterEditor();

//public slots:

//    void onShutdown();

//private:

//    std::unique_ptr<Clock>            clock;
//    //std::unique_ptr<Renderer>         renderer;
//    std::unique_ptr<OperatorNetwork>     project_model;
//    std::unique_ptr<OperatorNetworkView> project_view_model;
//    std::unique_ptr<ParameterEditor>     parameterEditor;
//    ExecutionEngine *                 m_executionEngine;
//    ExecutionEngineWindow*            m_executionEngineWindow;
//    QThread                           m_executionThread;

//    std::unique_ptr<Viewport> viewport;

//    std::unique_ptr<QWidget> m_mainWindow;
//    //std::unique_ptr<QOpenGLWidget> m_mainWindow;
//};
