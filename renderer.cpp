#include <unordered_set>
#include <iostream>

#include "renderer.h"
#include "model/programmodel.h"
#include "model/baseoperator.h"

#include <QThread>
#include <QApplication>



Renderer::Renderer()
{
    render_surface.setFormat(QSurfaceFormat::defaultFormat());
    render_surface.create();

    context.setFormat(QSurfaceFormat::defaultFormat());
    context.create();
    context.makeCurrent(&render_surface);


    initializeOpenGLFunctions();

    connect(&render_timer, &QTimer::timeout, this, &Renderer::render_frame);
}


Renderer::~Renderer()
{ }


void Renderer::set_model(ProgramModel* model_)
{
    if (model != nullptr)
    {
        model = model_;
        render_count = 0;
        render_timer.start(static_cast<int>(1000.0f / 60.0f));
    }
    else
    {
        model = nullptr;
        render_timer.stop();
    }
}



void Renderer::render_frame()
{
    context.makeCurrent(&render_surface);

    if (render_count % 120 == 0) std::cout <<"render " << QThread::currentThreadId() << "\n";

    int node_count = model->get_all_nodes().size();
    auto open_list = model->get_entry_nodes();
    std::unordered_set<BaseOperator*> rendered;
    /*
    while(static_cast<int>(rendered.size()) < node_count)
    {
        auto current = open_list.front();
        open_list.pop_front();

        bool inputs_rendered = true;

        for (int i = 0; i < current->get_num_inputs(); ++i)
        {
            // get_input(i) can be nullptr. Make sure been_rendered never contains nullptr!
            if (rendered.find(current->get_input(i)) == rendered.end())
            {
                inputs_rendered = false;
                break;
            }
        }

        if (inputs_rendered)
        {
            current->prepare_render();
            current->render();

            rendered.insert(current);
            // Now that current has been rendered, all children can be queued.
            for (int i = 0; i < current->get_num_inputs(); ++i)
            {
                // if the input is not nullptr and not in the queue yet.
                if (current->get_input(i) && open_list.count(current->get_input(i)) == 0)
                {
                    open_list.push_back(current->get_input(i));
                }
            }
        }
        else
        {
            // Node's inputs need to be evaluated before this one. Add current back to the
            // queue to try again later.
            open_list.push_back(current);
        }
    }*/

    ++render_count;
}
