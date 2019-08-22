#include "projectmodel.h"

#include "model/baseoperator.h"
#include "model/basedatatype.h"
#include "model/datainput.h"

#include "command/addcommand.h"
#include "command/removecommand.h"
#include "command/connectcommand.h"
#include "command/disconnectcommand.h"
#include "command/movecommand.h"

#include <QString>
#include <QPointer>

#include <iostream>




ProjectModel::ProjectModel(LibraryModel& library)
    : operator_library(library)
{ }


QUndoStack* ProjectModel::get_undo_stack()
{
    return &undo_stack;
}


void ProjectModel::redo()
{
    undo_stack.redo();
}


void ProjectModel::undo()
{
    undo_stack.undo();
}


void ProjectModel::add_operator(const OperatorTypeInfo& op_type, int x, int y)
{
    //undo_stack.beginMacro("Adding Operator");
    auto op = op_type.construct();

    op->set_position(x, y);
    undo_stack.push(new AddCommand(*this, op));
    //undo_stack.endMacro();
}


void ProjectModel::remove_operator(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        undo_stack.beginMacro("Remove Operator");

        for (auto& ptr : operator_ptr->data_inputs())
        {
            ptr->disconnect();
        }

        for (auto& ptr : operator_ptr->data_outputs())
        {
            ptr->disconnect_all();
        }
        // Maybe give BaseOperator a remove function?
        //undo_stack.beginMacro("remove command");
        //operator_ptr->
        undo_stack.push(new RemoveCommand(*this, operator_ptr));

        undo_stack.endMacro();
    }
}

/*
void ProgramModel::move_operator_undoable(BaseOperator * op, int x, int y)
{
    if (op && (x != op->get_position_x() || y != op->get_position_y()))
    {
        undo_stack.push(new MoveCommand(*op, x, y));
    }
}


void ProgramModel::connect_data_undoable(BaseDataBlock* output, DataBlockInput* input)
{
    if (output && input && input->compatible_with(output))
    {
        undo_stack.push(new ConnectCommand(output, input));
    }
}


void ProgramModel::disconnect_data_undoable(BaseDataBlock* output, DataBlockInput* input)
{
    if (output && input)
    {

    }
}*/




void ProjectModel::add_operator_to_model(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        auto blocks = operator_ptr->data_outputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->acquire_resources();
            }
        }
        operator_ptr->acquire_resources();

        operators.push_back(operator_ptr);
        emit operator_added(operator_ptr);
    }
}


void ProjectModel::remove_operator_from_model(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        operator_ptr->release_resources();

        auto blocks = operator_ptr->data_outputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->release_resources();
            }
        }

        operators.erase(std::remove(operators.begin(), operators.end(), operator_ptr), operators.end());
        emit operator_removed(operator_ptr);
    }
}


const std::vector<BaseOperator*>& ProjectModel::all_operators() const
{
    return operators;
}
