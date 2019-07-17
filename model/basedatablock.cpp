#include "basedatablock.h"
#include "model/datablockinput.h"
#include "model/programmodel.h"

#include "command/connectcommand.h"
#include "command/disconnectcommand.h"



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


bool BaseDataBlock::is_connected() const
{
    return !connections.empty();
}


bool BaseDataBlock::is_connected_to(const DataBlockInput* data_input) const
{
    return std::find(connections.begin(), connections.end(), data_input) != connections.end();
}


std::vector<const DataBlockInput*> BaseDataBlock::get_connections() const
{
    return std::vector<const DataBlockInput*>(connections.begin(), connections.end());
}


void BaseDataBlock::connect_to(DataBlockInput* data_input)
{
    if (data_input && data_input->compatible_with(this))
    {
        get_main_model()->get_undo_stack()->push(new ConnectCommand(this, data_input));
    }
}


// Undoable action
void BaseDataBlock::disconnect_from(DataBlockInput* data_input)
{
    if (is_connected_to(data_input))
    {
        get_main_model()->get_undo_stack()->push(new DisconnectCommand(this, data_input));
    }
}


// Undoable action
void BaseDataBlock::disconnect_all()
{
    if (!connections.empty())
    {
        get_main_model()->get_undo_stack()->beginMacro("disconnect all");

        while (!connections.empty())
        {
            disconnect_from(connections.back());
        }

        get_main_model()->get_undo_stack()->endMacro();
    }
}


// Non action version of connect_to
bool BaseDataBlock::add_connection(DataBlockInput* data_input)
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
bool BaseDataBlock::remove_connection(DataBlockInput* data_input)
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
