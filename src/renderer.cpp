#include <unordered_set>
#include <iostream>

#include "renderer.h"
#include "application.h"
#include "model/OperatorNetwork.hpp"
#include "model/BaseOperator.hpp"
#include "model/datainput.h"
#include "model/BaseDataType.hpp"
#include "utility/stdLibraryHelpers.hpp"

#include <QThread>
#include <QApplication>

#include <deque>


Renderer::Renderer(QOpenGLWidget* main_opengl)
{
    std::cout << QOpenGLContext::globalShareContext() << std::endl;
    //opengl_context.setFormat(main_opengl->format());
    //opengl_context.setShareContext(main_opengl->context());
    //opengl_context.create();

    opengl_surface.setFormat(QOpenGLContext::globalShareContext()->format());
    opengl_surface.create();


    QOpenGLContext::globalShareContext()->makeCurrent(&opengl_surface);
    initializeOpenGLFunctions();
}


Renderer::~Renderer()
{ }


void Renderer::set_model(OperatorNetwork* m)
{
    model = m;
}


bool has_turn(const BaseOperator* op, const std::unordered_set<const BaseOperator*>& closed_list)
{
    Q_ASSERT(op);

    for (auto& input : op->activeDataInputs())
    {
        auto connected_op = input->getConnectedData()->getOperator();

        // If a connected operator has not yet been processed that one has to process first,
        // thus return false: this operator does not yet have its turn.
        if (closed_list.count(connected_op) == 0)
        {
            return false;
        }
    }

    // If all inputs were looped through and they had all been processed already it's
    // this operators turn to be processed.
    return true;
}


void Renderer::render_frame()
{
    fps_monitor.frame();

    QOpenGLContext::globalShareContext()->makeCurrent(&opengl_surface);
    //opengl_context.makeCurrent(&opengl_surface);
    //opengl_widget.makeCurrent();

    std::deque<BaseOperator*> open_list;
    std::unordered_set<const BaseOperator*> closed_list;

    for (auto o : model->getOperators())
    {
        if (o->hasActiveDataInputs() == 0)
        {
            open_list.push_back(o);
        }
    }

    while (!open_list.empty())
    {
        auto current = open_list.front();
        open_list.pop_front();

        if (has_turn(current, closed_list))
        {
            current->prepare();
            current->updateParameters();
            current->run();

            closed_list.insert(current);

            for (auto& output : current->activeDataOutputs())
            {
                for (auto connected_input : output->getConnections())
                {
                    if (!contains(open_list, connected_input->getOperator()))
                    {
                        open_list.push_back(connected_input->getOperator());
                    }
                }
            }
        }
        else
        {
            open_list.push_back(current);
        }
    }

    if (fps_monitor.getFrameCount() % 500 == 0)
    {
        std::cout << fps_monitor.getFrameRate() << " fps in renderer.\n";
    }
    glFlush();
}
