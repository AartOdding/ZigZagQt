#include "model/data/datablockinput.h"
#include "model/data/basedatablock.h"



DataBlockInput::DataBlockInput(const char * data_block_type)
    : type_name(data_block_type)
{

}


DataBlockInput::~DataBlockInput()
{

}


bool DataBlockInput::compatible_with(const BaseDataBlock* data_block)
{
    if (data_block)
    {
        return strcmp(type_name, data_block->type_name) == 0;
    }
    return false;
}


std::vector<BaseParameter*> DataBlockInput::get_parameters()
{
    return {};
}


void DataBlockInput::refresh_parameters()
{
    emit parameters_modified();
}
