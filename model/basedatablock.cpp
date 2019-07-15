#include "basedatablock.h"
#include "model/datablockinput.h"



BaseDataBlock::BaseDataBlock(const char * data_type_name)
    : type_name(data_type_name)
{

}


BaseDataBlock::~BaseDataBlock()
{

}


void BaseDataBlock::refresh_parameters()
{
    emit parameters_modified();
}

/*
bool BaseDataBlock::connect_with(DataBlockInput* input)
{
    if (input && !connections.contains(input) && input->compatible_with(this))
    {

    }
    return false;
}


bool BaseDataBlock::disconnect_from(DataBlockInput* input)
{
    if (input && connections.contains(input))
    {

    }
    return false;
}
*/
