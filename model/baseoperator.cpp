#include "baseoperator.h"

#include "command/movecommand.h"
#include "model/programmodel.h"

#include <QPointer>



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
        cached_inputs = provide_inputs();
        inputs_cached = true;
    }
    return cached_inputs;
}


const std::vector<BaseDataBlock*>& BaseOperator::outputs()
{
    if (!outputs_cached)
    {
        cached_outputs = provide_outputs();
        outputs_cached = true;
    }
    return cached_outputs;
}


const std::vector<BaseParameter*>& BaseOperator::parameters()
{
    if (!parameters_cached)
    {
        cached_parameters = provide_parameters();
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
    cached_inputs = provide_inputs();
    emit inputs_modified();
}


void BaseOperator::refresh_outputs()
{
    cached_outputs = provide_outputs();
    emit outputs_modified();
}


void BaseOperator::refresh_parameters()
{
    cached_parameters = provide_parameters();
    emit parameters_modified();
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

/*
BaseOperator * BaseOperator::get_input(int index)
{
    if (index >= 0 && index < inputs.size())
    {
        return inputs[index];
    }
    else
    {
        return nullptr;
    }
}

int BaseOperator::get_num_inputs() const
{
    return inputs.size();
}

int BaseOperator::get_num_used_inputs() const
{

    int count = 0;

    for (auto& input : inputs)
    {
        if (input)
        {
            ++count;
        }
    }

    return inputs.size();
}

int BaseOperator::get_num_output_users() const
{
    int count = 0;
    for (auto& o : output_users)
    {
        if (o) ++count;
    }
    return count;
}
*/


/*
Policy BaseOperator::get_resolution_policy() const
{
    return resolution_policy;
}

Policy BaseOperator::get_pixel_type_policy() const
{
    return pixel_type_policy;
}
*/

// SLOTS

/*
void BaseOperator::set_input(int index, BaseOperator* operator_)
{

    if (index >= 0 && index != static_cast<int>(inputs.size()))
    {
        if (inputs[index] != operator_)
        {
            if (inputs[index]) // First properly remove old connection
            {
                inputs[index]->output_users.removeOne(this);
            }

            inputs[index] = operator_;

            if (operator_)
            {
                operator_->output_users.append(this);
            }
            emit input_changed(index);
        }
    }

}

void BaseOperator::set_num_inputs(int new_num_inputs)
{
    if (new_num_inputs >= 0 && new_num_inputs != inputs.size())
    {
        inputs.resize(new_num_inputs);
        emit num_inputs_changed(new_num_inputs);
    }
}
*/



/*
void BaseOperator::set_resolution_policy(Policy new_policy)
{
    if (resolution_policy != new_policy)
    {
        resolution_policy = new_policy;
        emit resolution_policy_changed(new_policy);
    }
}

void BaseOperator::set_pixel_type_policy(Policy new_policy)
{
    if (pixel_type_policy != new_policy)
    {
        pixel_type_policy = new_policy;
        emit pixel_type_policy_changed(new_policy);
    }
}
*/

