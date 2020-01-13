#include "BaseDataType.hpp"
#include "model/datainput.h"
#include "model/projectmodel.h"
#include "model/BaseOperator.hpp"

#include "command/connectcommand.h"
#include "command/disconnectcommand.h"

#include "zigzaglib/xmlserializer.h"

#include "application.h"



BaseDataType::BaseDataType(BaseOperator* parent, const QString& name, const DataTypeDescription& description)
    : BaseZigZagObject(parent, name),
      m_parentOperator(parent),
      m_description(&description)
{
    Q_ASSERT(parent);
}


BaseDataType::~BaseDataType()
{

}


const DataTypeDescription * BaseDataType::getDescription() const
{
    return m_description;
}


bool BaseDataType::isConnected() const
{
    return !m_connections.empty();
}


bool BaseDataType::isConnectedTo(const DataInput* data_input) const
{
    return std::find(m_connections.begin(), m_connections.end(), data_input) != m_connections.end();
}


const std::vector<DataInput*>& BaseDataType::getConnections() const
{
    return m_connections;
}


void BaseDataType::connectTo(DataInput* data_input)
{
    if (data_input && data_input->get_connection() != this && data_input->compatible_with(this))
    {
        auto undo = network()->get_undo_stack();
        undo->push(new ConnectCommand(this, data_input));
    }
}


// Undoable action
void BaseDataType::disconnectFrom(DataInput* data_input)
{
    if (isConnectedTo(data_input))
    {
        application::project_model()->get_undo_stack()->push(new DisconnectCommand(this, data_input));
    }
}


// Undoable action
void BaseDataType::disconnectFromAll()
{
    if (!m_connections.empty())
    {
        application::project_model()->get_undo_stack()->beginMacro("Disconnect All");

        while (!m_connections.empty())
        {
            disconnectFrom(m_connections.back());
        }

        application::project_model()->get_undo_stack()->endMacro();
    }
}


// Non action version of connect_to
bool BaseDataType::addConnection(DataInput* data_input)
{
    if (data_input && data_input->compatible_with(this) && !isConnectedTo(data_input))
    {
        m_connections.push_back(data_input);
        emit hasConnected(this, data_input);
        return true;
    }
    return false;
}


// Non action version of connect_to
bool BaseDataType::removeConnection(DataInput* data_input)
{
    auto location = std::find(m_connections.begin(), m_connections.end(), data_input);

    if (location != m_connections.end())
    {
        std::swap(*location, m_connections.back());
        m_connections.pop_back();
        emit hasDisconnected(this, data_input);
        return true;
    }
    return false;
}


BaseOperator* BaseDataType::getOperator() const
{
    return m_parentOperator;
}
