#include "model/operator/baseoperator.h"
#include "model/program/programmodel.h"

#include <QPointer>



BaseOperator::BaseOperator(ProgramModel& model_)
    : QObject(&model_), model(model_)
{



    //input = nullptr;

    //inputs = QVector<QPointer<BaseTOP>>(6);

    for (int i = 0; i < 4; ++i)
    {
        //inputs.append(nullptr);
    }
}


BaseOperator::~BaseOperator()
{

}



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
    /*
    int count = 0;

    for (auto& input : inputs)
    {
        if (input)
        {
            ++count;
        }
    }
    */
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



int BaseOperator::get_position_x() const
{
    return position_x;
}

int BaseOperator::get_position_y() const
{
    return position_y;
}

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

void BaseOperator::set_input(int index, BaseOperator* operator_)
{
    /*
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
    */
}

void BaseOperator::set_num_inputs(int new_num_inputs)
{
    if (new_num_inputs >= 0 && new_num_inputs != inputs.size())
    {
        inputs.resize(new_num_inputs);
        emit num_inputs_changed(new_num_inputs);
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

