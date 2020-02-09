#include "ExecutionEngine.hpp"
#include "OperatorNetwork.hpp"
#include "BaseOperator.hpp"
#include "datainput.h"
#include "view/ExecutionEngineWindow.hpp"
#include "utility/stdLibraryHelpers.hpp"
#include "library/standard/texture/texturedata.h"

#include <QElapsedTimer>
#include <QSemaphore>
#include <QRandomGenerator>
#include <QThread>

#include <iostream>
#include <deque>
#include <unordered_set>


static bool hasTurn(const BaseOperator* op, const std::unordered_set<const BaseOperator*>& doneList)
{
    for (auto& input : op->activeDataInputs())
    {
        auto preceedingOperator = input->getConnectedData()->getOperator();

        // If a connected operator has not yet been processed that one has to process first,
        // thus return false: this operator does not yet have its turn.
        if (doneList.count(preceedingOperator) == 0)
        {
            return false;
        }
    }

    // If all inputs were looped through and they had all been processed already it's
    // this operators turn to be processed.
    return true;
}



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
}


void ExecutionEngine::pauseExecution()
{
    std::cout << "PAUSE: " << thread() << std::endl;
    m_timer.stop();
}


void ExecutionEngine::executeFrame()
{
    m_glWindow->makeCurrent();

    std::deque<BaseOperator*> openList;
    std::unordered_set<const BaseOperator*> closedList;
    std::vector<BaseOperator*> orderedClosedList;

    orderedClosedList.reserve(m_network->getOperators().size());

    for (auto op : m_network->getOperators())
    {
        if (op->hasActiveDataInputs() == 0)
        {
            openList.push_back(op);
        }
    }

    while (!openList.empty())
    {
        auto current = openList.front();
        openList.pop_front();

        if (hasTurn(current, closedList))
        {
            current->prepare();
            current->updateParameters();
            current->run();

            closedList.insert(current);
            orderedClosedList.push_back(current);

            for (auto& output : current->activeDataOutputs())
            {
                for (auto connected_input : output->getConnections())
                {
                    if (!contains(openList, connected_input->getOperator()))
                    {
                        openList.push_back(connected_input->getOperator());
                    }
                }
            }
        }
        else
        {
            openList.push_back(current);
        }
    }

    TextureData* lastRenderedTexture = nullptr;

    for (int i = orderedClosedList.size()-1; i >= 0 && !lastRenderedTexture; --i)
    {
        auto op = orderedClosedList[i]; // op = last rendered operator
        auto outputs = op->dataOutputs();

        for (auto out : outputs)
        {
            if (dynamic_cast<TextureData*>(out))
            {
                lastRenderedTexture = static_cast<TextureData*>(out);
                break;
            }
        }
    }

    if (lastRenderedTexture)
    {

    }

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
