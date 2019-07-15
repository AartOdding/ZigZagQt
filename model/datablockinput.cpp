#include "datablockinput.h"

#include "model/basedatablock.h"



DataBlockInput::DataBlockInput(const char * data_block_type)
    : type_name(data_block_type)
{

}


DataBlockInput::~DataBlockInput()
{

}


std::vector<BaseParameter*> DataBlockInput::get_parameters()
{
    return {};
}


void DataBlockInput::refresh_parameters()
{
    emit parameters_modified();
}


bool DataBlockInput::compatible_with(const BaseDataBlock* data_block)
{
    if (data_block)
    {
        return strcmp(type_name, data_block->type_name) == 0;
    }
    return false;
}


bool DataBlockInput::connect_to(BaseDataBlock* data_block)
{
    if (data_block && connection != data_block && compatible_with(data_block))
    {
        if (connection)
        {

        }

        connection = data_block; // Now is_connected() will return true, important for next lines

        if (!data_block->is_connected_to(this))
        {
            data_block->connect_to(this);
        }

        emit connected_to()
    }
}


bool DataBlockInput::disconnect()
{

}


bool DataBlockInput::is_connected() const
{

}


bool DataBlockInput::is_connected_to(BaseDataBlock* data_block) const
{

}


BaseDataBlock* DataBlockInput::get_connection() const
{

}
