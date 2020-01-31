#include "ExecutionEngine.hpp"
#include "OperatorNetwork.hpp"

#include <QElapsedTimer>
#include <QSemaphore>
#include <QThread>
#include <iostream>



ExecutionEngine::ExecutionEngine(OperatorNetwork* network)
    : m_timer(this),
      m_network(network)
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
    m_timer.start(1000);
}


void ExecutionEngine::pauseExecution()
{
    std::cout << "PAUSE: " << thread() << std::endl;
    m_timer.stop();
}

/*
void ExecutionEngine::blockEventLoop(QSemaphore* semaphore)
{
    QElapsedTimer timer;
    timer.start();

    semaphore->acquire(); // STOOPID = DEADLOCK

    auto ns = timer.nsecsElapsed();
    std::cout << "Execution thread was blocked for: " << ns << " ns" << std::endl;
}
*/


void ExecutionEngine::executeFrame()
{
    std::cout << "EXECUTE: " << thread() << std::endl;
}
