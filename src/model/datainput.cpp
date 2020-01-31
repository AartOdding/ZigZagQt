#include "datainput.h"

#include "application.h"
#include "model/BaseOperator.hpp"
#include "model/OperatorNetwork.hpp"
#include "command/connectcommand.h"
#include "command/disconnectcommand.h"



DataInput::DataInput(BaseOperator* parent_op, const QString& name, const DataTypeDescription& type_info)
    : BaseZigZagObject(parent_op, name),
      m_parent_operator(parent_op),
      data_type(&type_info)
{
    Q_ASSERT(parent_op);
}


DataInput::~DataInput()
{

}

BaseOperator* DataInput::get_operator() const
{
    return m_parent_operator;
}

const DataTypeDescription * DataInput::type() const
{
    return data_type;
}


bool DataInput::compatible_with(const BaseDataType* data) const
{
    if (data)
    {
        return type()->name == data->getDescription()->name;
    }
    return false;
}


void DataInput::connect_to(BaseDataType* new_connection)
{
    if (new_connection != connection)
    {
        if (new_connection == nullptr)
        {
            disconnect(); // Setting connection to nullptr is same as disconnecting.
        }
        else
        {
            if (compatible_with(new_connection))
            {
                application::project_model()->get_undo_stack()->push(new ConnectCommand(new_connection, this));
            }
        }
    }
}


void DataInput::disconnect()
{
    if (connection)
    {
        application::project_model()->get_undo_stack()->push(new DisconnectCommand(connection, this));
    }
}


bool DataInput::set_connection(BaseDataType *new_connection)
{
    if (new_connection == nullptr || compatible_with(new_connection))
    {
        /*
         * If the new connection between the data block, and this data input
         * is not compatible, we rather not change anything, than just disconnect.
         */

        if (new_connection != connection)
        {
            /*
             * Scenario's:
             * - there was a connection, still a connection after
             * - there was not a connection, connection after
             * - there was a connection, nullptr after
             */

            if (connection)
            {
                auto old_connection = connection;
                connection = nullptr;
                emit has_disconnected(old_connection, this);
            }

            Q_ASSERT(connection == nullptr); // Just for good measure.

            if (new_connection)
            {
                connection = new_connection;
                emit has_connected(new_connection, this);
            }

            return true;
        }
    }
    return false;
}


bool DataInput::is_connected() const
{
    return static_cast<bool>(connection);
}


bool DataInput::is_connected_to(const BaseDataType* data_block) const
{
    return connection == data_block;
}


const BaseDataType* DataInput::get_connection() const
{
    return connection;
}

