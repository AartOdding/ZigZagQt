#include "datainput.h"

#include "application.h"
#include "model/basedatatype.h"
#include "model/baseoperator.h"
#include "model/projectmodel.h"
#include "command/connectcommand.h"
#include "command/disconnectcommand.h"


DataInput::DataInput(BaseOperator* parent_operator_, const char * name_, const DataTypeInfo& type_info_)
    : ParameterOwner(parent_operator_), parent_operator(parent_operator_), m_name(name_), type_info(&type_info_)
{
    parent_operator->register_data_input(this);
}


DataInput::~DataInput()
{

}


const DataTypeInfo * DataInput::type() const
{
    return type_info;
}


const char * DataInput::name() const
{
    return m_name;
}


bool DataInput::compatible_with(const BaseDataType* data_block) const
{
    if (data_block)
    {
        return type_info->name == data_block->type()->name;
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
