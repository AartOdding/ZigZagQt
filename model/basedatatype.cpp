#include "basedatatype.h"
#include "model/datainput.h"
#include "model/projectmodel.h"
#include "model/baseoperator.h"

#include "command/connectcommand.h"
#include "command/disconnectcommand.h"

#include "zigzaglib/xmlserializer.h"

#include "application.h"



BaseDataType::BaseDataType(BaseOperator* parent_op, const char * name, const DataTypeInfo& type_info)
    : BaseParameterOld(parent_op, ParameterType::DataOutput, name), data_type(&type_info)
{
    Q_ASSERT(parent_op);
    parent_op->register_data_output(this);
}


BaseDataType::~BaseDataType()
{

}


const DataTypeInfo * BaseDataType::type() const
{
    return data_type;
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
        emit has_connected(this, data_input);
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
        emit has_disconnected(this, data_input);
        return true;
    }
    return false;
}


void BaseDataType::set_from_xml(QXmlStreamReader& xml)
{

}


void BaseDataType::write_to_xml(XmlSerializer& xml)
{
    xml.begin_element("BaseDataType");
    xml.add_int_attribute("id", xml.id(this));
        BaseParameterOld::write_to_xml(xml);
        xml.begin_element("connections");
        xml.add_int_attribute("size", connections.size());
            for (auto connection : connections)
            {
                xml.add_int_element("connection", xml.id(connection));
            }
        xml.end_element();

    xml.end_element();
}
