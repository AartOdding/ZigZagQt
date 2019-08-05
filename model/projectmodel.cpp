#include "projectmodel.h"

#include "model/baseoperator.h"
#include "model/basedatablock.h"
#include "model/datablockinput.h"

#include "command/addcommand.h"
#include "command/removecommand.h"
#include "command/connectcommand.h"
#include "command/disconnectcommand.h"
#include "command/movecommand.h"

#include <QString>
#include <QPointer>

#include <iostream>




ProjectModel::ProjectModel(OperatorLibrary& library)
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


void ProjectModel::add_operator(const char * operator_class, int x, int y)
{
    if (operator_library.contains_operator_type(operator_class))
    {
        //undo_stack.beginMacro("Adding Operator");
        auto op = operator_library.create_operator(operator_class);
        op->set_position(x, y);
        undo_stack.push(new AddCommand(*this, op));
        //undo_stack.endMacro();
    }
}


void ProjectModel::remove_operator(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        undo_stack.beginMacro("Remove Operator");

        for (auto& ptr : operator_ptr->inputs())
        {
            ptr->disconnect();
        }

        for (auto& ptr : operator_ptr->outputs())
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
        auto blocks = operator_ptr->outputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->acquire_resources();
            }
        }
        operator_ptr->acquire_resources();

        emit operator_added(operator_ptr);
    }
}


void ProjectModel::remove_operator_from_model(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        operator_ptr->release_resources();

        auto blocks = operator_ptr->outputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->release_resources();
            }
        }
        emit operator_removed(operator_ptr);
    }
}


QList<BaseOperator*> ProjectModel::get_entry_nodes()
{
    /*
    auto all_children = findChildren<BaseOperator*>();
    QList<BaseOperator*> entry_points;

    for (auto child : all_children)
    {
        if (child->get_num_used_inputs() == 0)
        {
            entry_points.push_back(child);
        }
    }
    return entry_points;
    */
    return QList<BaseOperator*>();
}


QList<BaseOperator*> ProjectModel::get_all_nodes()
{
    return findChildren<BaseOperator*>();
}
