#include "baseoperator.h"
#include "basedatatype.h"
#include "application.h"

#include "command/movecommand.h"
#include "command/removecommand.h"
#include "model/projectmodel.h"
#include "model/datainput.h"

#include "zigzaglib/xmlserializer.h"

#include <QPointer>

#include <algorithm>




BaseOperator::BaseOperator(const OperatorTypeInfo& type_)
    : BaseParameter(nullptr, ParameterType::Operator, type_.name.c_str()), type_info(&type_)
{

}


BaseOperator::~BaseOperator()
{

}


void BaseOperator::update_view()
{
    emit update_view_requested();
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
    application::project_model()->remove_operator(this);
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


const std::vector<BaseParameterComponent*>& BaseOperator::importing_parameters() const
{
    return m_importing_parameters;
}


const std::vector<BaseParameterComponent*>& BaseOperator::exporting_parameters() const
{
    return m_exporting_parameters;
}


void BaseOperator::set_from_xml(QXmlStreamReader& xml)
{

}


void BaseOperator::write_to_xml(XmlSerializer& xml)
{
    xml.begin_element("BaseOperator");
    xml.add_int_attribute("id", xml.id(this));

        BaseParameter::write_to_xml(xml);

        xml.add_int_element("position_x", position_x);
        xml.add_int_element("position_y", position_y);

        xml.begin_element("inputs");
        xml.add_int_attribute("size", inputs.size());
            for (auto in : inputs)
            {
                in->write_to_xml(xml);
            }
        xml.end_element(); // ends inputs

        xml.begin_element("outputs");
        xml.add_int_attribute("size", outputs.size());
            for (auto out : outputs)
            {
                out->write_to_xml(xml);
            }
        xml.end_element(); // ends outputs

    xml.end_element();
}
