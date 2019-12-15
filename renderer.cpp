#include <unordered_set>
#include <iostream>

#include "renderer.h"
#include "application.h"
#include "model/projectmodel.h"
#include "model/baseoperator.h"
#include "model/datainput.h"
#include "model/basedatatype.h"
#include "utility/std_containers_helpers.h"

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


void Renderer::set_model(ProjectModel* m)
{
    model = m;
}


bool has_turn(const BaseOperator* op, const std::unordered_set<const BaseOperator*>& closed_list)
{
    Q_ASSERT(op);

    for (auto& input : op->used_data_inputs())
    {
        auto connected_op = input->get_connection()->get_operator();

        // If a connected operator has not yet been processed that one has to process first,
        // thus return false: this operator does not yet have its turn.
        if (closed_list.count(connected_op) == 0)
        {
            return false;
        }
    }

    for (auto par : op->importing_parameters())
    {
        if (closed_list.count(par->getImport()->getParameter()->findParent<BaseOperator*>()) == 0)
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

    for (auto o : model->all_operators())
    {
        if (o->count_used_data_inputs() == 0 && o->importing_parameters().empty())
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

            for (auto& output : current->used_data_outputs())
            {
                for (auto connected_input : output->get_connections())
                {
                    if (!contains(open_list, connected_input->get_operator()))
                    {
                        open_list.push_back(connected_input->get_operator());
                    }
                }
            }
            for (auto par : current->exporting_parameters())
            {
                for (auto importer : par->getExports())
                {
                    if (!contains(open_list, importer->getParameter()->findParent<BaseOperator*>()))
                    {
                        open_list.push_back(importer->getParameter()->findParent<BaseOperator*>());
                    }
                }
            }
        }
        else
        {
            open_list.push_back(current);
        }
    }

    if (fps_monitor.frame_count() % 500 == 0)
    {
        std::cout << fps_monitor.fps() << " fps in renderer.\n";
    }
    glFlush();
}
