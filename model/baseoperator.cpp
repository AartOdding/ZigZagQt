#include "baseoperator.h"

#include "command/movecommand.h"
#include "command/removecommand.h"
#include "model/programmodel.h"
#include "model/datablockinput.h"

#include <QPointer>



// helper function to remove nullptrs from a vector
template<typename T>
static std::vector<T*> no_nullptr(std::vector<T*> vec)
{
    for (int i = vec.size() - 1; i >= 0; --i)
    {
        if (!vec[i])
        {
            vec.erase(vec.begin() + i);
        }
    }
    return vec;
}


BaseOperator::BaseOperator()
{
}


BaseOperator::~BaseOperator()
{
}


const std::vector<DataBlockInput*>& BaseOperator::inputs()
{
    if (!inputs_cached)
    {
        cached_inputs = no_nullptr(provide_inputs());

        for (auto ptr : cached_inputs)
        {
            ptr->set_parent_operator(this);
        }
        inputs_cached = true;
    }
    return cached_inputs;
}


const std::vector<BaseDataBlock*>& BaseOperator::outputs()
{
    if (!outputs_cached)
    {
        cached_outputs = no_nullptr(provide_outputs());

        for (auto ptr : cached_outputs)
        {
            ptr->set_parent_operator(this);
        }

        outputs_cached = true;
    }
    return cached_outputs;
}


const std::vector<BaseParameter*>& BaseOperator::parameters()
{
    if (!parameters_cached)
    {
        cached_parameters = no_nullptr(provide_parameters());
        parameters_cached = true;
    }
    return cached_parameters;
}


int BaseOperator::get_position_x() const
{
    return position_x;
}


int BaseOperator::get_position_y() const
{
    return position_y;
}


void BaseOperator::refresh_inputs()
{
    auto new_inputs = no_nullptr(provide_inputs());

    if (cached_inputs != new_inputs)
    {
        std::swap(cached_inputs, new_inputs);

        for (auto ptr : cached_inputs)
        {
            if (ptr)
            {
                ptr->set_parent_operator(this);
            }
        }
        emit inputs_modified();
    }
}


void BaseOperator::refresh_outputs()
{
    auto new_outputs = no_nullptr(provide_outputs());

    if (cached_outputs != new_outputs)
    {
        std::swap(cached_outputs, new_outputs);

        for (auto ptr : cached_outputs)
        {
            if (ptr)
            {
                ptr->set_parent_operator(this);
            }
        }
        emit outputs_modified();
    }
}


void BaseOperator::refresh_parameters()
{
    auto new_parameters = no_nullptr(provide_parameters());

    if (cached_parameters != new_parameters)
    {
        std::swap(cached_parameters, new_parameters);
        emit parameters_modified();
    }
}


void BaseOperator::remove()
{
    auto model = get_main_model();
    auto undo_stack = model->get_undo_stack();

    undo_stack->beginMacro("Remove Operator");

    for (auto ptr : cached_inputs)
    {
        ptr->disconnect();
    }

    for (auto ptr : cached_outputs)
    {
        ptr->disconnect_all();
    }

    undo_stack->push(new RemoveCommand(*model, this));
    undo_stack->endMacro();
}


void BaseOperator::move_to(int pos_x, int pos_y)
{
    if (position_x != pos_x || position_y != pos_y)
    {
        get_main_model()->get_undo_stack()->push(new MoveCommand(*this, pos_x, pos_y));
    }
}


void BaseOperator::set_position(int pos_x, int pos_y)
{
    if (position_x != pos_x || position_y != pos_y)
    {
        position_x = pos_x;
        position_y = pos_y;

        emit position_changed(pos_x, pos_y);
    }
}
