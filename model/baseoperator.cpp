#include "baseoperator.h"
#include "application.h"

#include "command/movecommand.h"
#include "command/removecommand.h"
#include "model/projectmodel.h"
#include "model/datainput.h"

#include <QPointer>

#include <algorithm>



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


BaseOperator::BaseOperator(const OperatorTypeInfo& type_)
    : type_info(&type_)
{

}


BaseOperator::~BaseOperator()
{

}


int BaseOperator::get_position_x() const
{
    return position_x;
}


int BaseOperator::get_position_y() const
{
    return position_y;
}


const OperatorTypeInfo * BaseOperator::type() const
{
    return type_info;
}


void BaseOperator::remove()
{
    auto model = application::project_model();
    auto undo_stack = model->get_undo_stack();

    undo_stack->beginMacro("Remove Operator");

    for (auto ptr : inputs)
    {
        ptr->disconnect();
    }

    for (auto ptr : outputs)
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
        application::project_model()->get_undo_stack()->push(new MoveCommand(*this, pos_x, pos_y));
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



const std::vector<DataInput*>& BaseOperator::data_inputs() const
{
    return inputs;
}


const std::vector<BaseDataType*>& BaseOperator::data_outputs() const
{
    return outputs;
}


std::vector<DataInput*> BaseOperator::used_data_inputs() const
{
    std::vector<DataInput*> result;
    result.reserve(inputs.size());

    for (const auto& input : inputs)
    {
        if (input->is_connected())
        {
            result.push_back(input);
        }
    }
    return result;
}


std::vector<BaseDataType*> BaseOperator::used_data_outputs() const
{
    std::vector<BaseDataType*> result;
    result.reserve(outputs.size());

    for (const auto& output : outputs)
    {
        if (output->is_connected())
        {
            result.push_back(output);
        }
    }
    return result;
}


int BaseOperator::count_used_data_inputs() const
{
    return std::count_if(
                inputs.begin(),
                inputs.end(),
                [](const auto& i){ return i->is_connected(); });
}


void BaseOperator::register_data_input(DataInput* input)
{
    if (input)
    {
        if (std::find(inputs.begin(), inputs.end(), input) == inputs.end())
        {
            inputs.push_back(input);
            emit data_input_added(input);
        }
    }
}


void BaseOperator::register_data_output(BaseDataType* output)
{
    if (output)
    {
        if (std::find(outputs.begin(), outputs.end(), output) == outputs.end())
        {
            outputs.push_back(output);
            emit data_output_added(output);
        }
    }
}

