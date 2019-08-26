#include <unordered_set>
#include <iostream>

#include "renderer.h"
#include "application.h"
#include "model/projectmodel.h"
#include "model/baseoperator.h"
#include "model/datainput.h"

#include <QThread>
#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <deque>


Renderer::Renderer()
{
    connect(&render_timer, &QTimer::timeout, this, &Renderer::render_frame);
}


Renderer::~Renderer()
{ }


void Renderer::set_model(ProjectModel* m)
{
    std::cout << "model: " << m << "\n";
    if (m != nullptr)
    {
        model = m;
        render_count = 0;
        std::cout << "startin\'\n";
        render_timer.start(17);
    }
    else
    {
        model = nullptr;
        render_timer.stop();
    }
}


bool has_turn(const BaseOperator* op, const std::unordered_set<const BaseOperator*>& closed_list)
{
    if (op)
    {
        for (auto& input : op->used_data_inputs())
        {
            auto connected_op = input->get_connection()->parent_operator;

            /*
             * If a connected operator has not yet been processed that one has to process first,
             * thus return false: this operator does not yet have its turn.
             */
            if (closed_list.count(connected_op) == 0)
            {
                return false;
            }
        }

        /*
         *  If all inputs were looped through and they had all been processed already it's
         *  this operators turn to be processed.
         */
        return true;
    }
    return false;
}


void Renderer::render_frame()
{
    ++render_count;
    fps_monitor.frame();

    Q_ASSERT(QOpenGLContext::currentContext());
    auto gl = QOpenGLContext::currentContext()->functions();
    GLint initial_fbo;
    gl->glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &initial_fbo);

    std::deque<BaseOperator*> open_list;
    std::unordered_set<const BaseOperator*> closed_list;

    for (auto o : model->all_operators())
    {
        if (o->count_used_data_inputs() == 0)
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
            current->run();
            closed_list.insert(current);

            for (auto& output : current->used_data_outputs())
            {
                for (auto connected_input : output->get_connections())
                {
                    open_list.push_back(connected_input->parent_operator);
                }
            }
        }
        else
        {
            open_list.push_back(current);
        }
    }
    application::project_view_model()->update();
    gl->glBindFramebuffer(GL_FRAMEBUFFER, initial_fbo);


}
