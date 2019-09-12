#include "basedatatype.h"
#include "model/datainput.h"
#include "model/projectmodel.h"
#include "model/baseoperator.h"

#include "command/connectcommand.h"
#include "command/disconnectcommand.h"

#include "application.h"



BaseDataType::BaseDataType(BaseOperator* parent_operator_, const DataTypeInfo& type_info_, const char * name_)
    : ParameterOwner(parent_operator_), parent_operator(parent_operator_), m_name(name_), m_type(&type_info_)
{
    Q_ASSERT(parent_operator);
    parent_operator->register_data_output(this);
}


BaseDataType::~BaseDataType()
{

}


const char * BaseDataType::name() const
{
    return m_name;
}


const DataTypeInfo * BaseDataType::type() const
{
    return m_type;
}


bool BaseDataType::is_connected() const
{
    return !connections.empty();
}


bool BaseDataType::is_connected_to(const DataInput* data_input) const
{
    return std::find(connections.begin(), connections.end(), data_input) != connections.end();
}


const std::vector<DataInput*>& BaseDataType::get_connections() const
{
    return connections;
}


void BaseDataType::connect_to(DataInput* data_input)
{
    if (data_input && data_input->get_connection() != this && data_input->compatible_with(this))
    {
        auto undo = application::project_model()->get_undo_stack();
        undo->push(new ConnectCommand(this, data_input));
    }
}


// Undoable action
void BaseDataType::disconnect_from(DataInput* data_input)
{
    if (is_connected_to(data_input))
    {
        application::project_model()->get_undo_stack()->push(new DisconnectCommand(this, data_input));
    }
}


// Undoable action
void BaseDataType::disconnect_all()
{
    if (!connections.empty())
    {
        application::project_model()->get_undo_stack()->beginMacro("Disconnect All");

        while (!connections.empty())
        {
            disconnect_from(connections.back());
        }

        application::project_model()->get_undo_stack()->endMacro();
    }
}


// Non action version of connect_to
bool BaseDataType::add_connection(DataInput* data_input)
{
    if (data_input && data_input->compatible_with(this) && !is_connected_to(data_input))
    {
        connections.push_back(data_input);
        emit connected_to(data_input);
        return true;
    }
    return false;
}


// Non action version of connect_to
bool BaseDataType::remove_connection(DataInput* data_input)
{
    auto location = std::find(connections.begin(), connections.end(), data_input);

    if (location != connections.end())
    {
        std::swap(*location, connections.back());
        connections.pop_back();
        emit disconnected_from(data_input);
        return true;
    }
    return false;
}
