#include "ExecutionEngine.hpp"
#include "OperatorNetwork.hpp"
#include "view/ExecutionEngineWindow.hpp"

#include <QElapsedTimer>
#include <QSemaphore>
#include <QRandomGenerator>
#include <QThread>
#include <iostream>



ExecutionEngine::ExecutionEngine(OperatorNetwork* network, ExecutionEngineWindow* window)
    : m_timer(this),
      m_network(network),
      m_glWindow(window),
      m_frameRateMonitor(500ms)
{
    m_network->setParent(this); // take ownership
    connect(&m_timer, &QTimer::timeout, this, &ExecutionEngine::executeFrame);
}


ExecutionEngine::~ExecutionEngine()
{

}


void ExecutionEngine::startExecution()
{
    std::cout << "START: " << thread() << std::endl;
    m_timer.start(20);

    m_glWindow->makeCurrent();
    initializeOpenGLFunctions();
    //m_glWindow->doneCurrent();
}


void ExecutionEngine::pauseExecution()
{
    std::cout << "PAUSE: " << thread() << std::endl;
    m_timer.stop();
}


void ExecutionEngine::executeFrame()
{
    //if (QOpenGLContext::currentContext() != m_glWindow->context())
    {

    }
    m_glWindow->makeCurrent();

    glClearColor(QRandomGenerator::global()->bounded(1.0), 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    m_glWindow->swapBuffers();


    m_frameRateMonitor.frame();

    if (m_frameRateMonitor.getFrameCount() == 120)
    {
        m_frameRateMonitor.resetFrameCount();
        std::cout << "Execution engine running at: " << m_frameRateMonitor.getFrameRate() << " fps\n";// << std::endl;
    }
}
