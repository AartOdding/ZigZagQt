#include <unordered_set>
#include <iostream>

#include "renderer.h"
#include "model/projectmodel.h"
#include "model/baseoperator.h"
#include "model/datainput.h"

#include <QThread>
#include <QApplication>

#include <deque>


Renderer::Renderer()
{
    connect(&render_timer, &QTimer::timeout, this, &Renderer::render_frame);
}


Renderer::~Renderer()
{ }


void Renderer::set_model(ProjectModel* model_)
{
    if (model != nullptr)
    {
        model = model_;
        render_count = 0;
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
    //std::cout << "r\n";
    ++render_count;
    fps_monitor.frame();

    if (render_count % 60 == 0)
    {
        //std::cout << fps_monitor.fps() << "\n";
    }

    int count = 0;

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

    //if (render_count % 120 == 0) std::cout <<"render " << QThread::currentThreadId() << "\n";

    //int node_count = model->get_all_nodes().size();
    //auto open_list = model->get_entry_nodes();
    //std::unordered_set<BaseOperator*> rendered;
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

    //++render_count;
}
