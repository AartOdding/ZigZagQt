#include "BaseDataType.hpp"
#include "model/datainput.h"
#include "model/OperatorNetwork.hpp"
#include "model/BaseOperator.hpp"

#include "command/connectcommand.h"
#include "command/disconnectcommand.h"

#include "app.h"



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


// Undoable action
void BaseDataType::connectTo(DataInput* dataInput)
{
    if (dataInput && dataInput->getConnectedData() != this && dataInput->compatible_with(this))
    {
        network()->getUndoStack()->push(new ConnectCommand(this, dataInput));
    }
}


// Undoable action
void BaseDataType::disconnectFrom(DataInput* data_input)
{
    if (isConnectedTo(data_input))
    {
        network()->getUndoStack()->push(new DisconnectCommand(this, data_input));
    }
}


// Undoable action
void BaseDataType::disconnectFromAll()
{
    if (!m_connections.empty())
    {
        network()->getUndoStack()->beginMacro("Disconnect All");

        while (!m_connections.empty())
        {
            disconnectFrom(m_connections.back());
        }

        network()->getUndoStack()->endMacro();
    }
}


// Non action version of connect_to
bool BaseDataType::addConnection(DataInput* dataInput)
{
    if (dataInput && dataInput->compatible_with(this) && !isConnectedTo(dataInput))
    {
        m_connections.push_back(dataInput);
        emit dataInput->getOperator()->dataConnected(m_parentOperator, this, dataInput->getOperator(), dataInput);
        return true;
    }
    return false;
}


// Non action version of connect_to
bool BaseDataType::removeConnection(DataInput* dataInput)
{
    auto location = std::find(m_connections.begin(), m_connections.end(), dataInput);

    if (location != m_connections.end())
    {
        std::swap(*location, m_connections.back());
        m_connections.pop_back();
        emit dataInput->getOperator()->dataDisconnected(m_parentOperator, this, dataInput->getOperator(), dataInput);
        return true;
    }
    return false;
}


BaseOperator* BaseDataType::getOperator() const
{
    return m_parentOperator;
}
