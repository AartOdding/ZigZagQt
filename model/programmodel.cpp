#include "programmodel.h"

#include "model/baseoperator.h"
#include "model/basedatablock.h"

#include "command/addcommand.h"
#include "command/removecommand.h"
#include "command/connectcommand.h"
#include "command/disconnectcommand.h"
#include "command/movecommand.h"

#include <QString>
#include <QPointer>

#include <iostream>




ProgramModel::ProgramModel(OperatorLibrary& library)
    : operator_library(library)
{ }


void ProgramModel::redo()
{
    std::cout << "redo\n";
    undo_stack.redo();
}


void ProgramModel::undo()
{
    std::cout << "undo\n";
    undo_stack.undo();
}


void ProgramModel::add_operator_undoable(const char * operator_class, int x, int y)
{
    if (operator_library.contains_operator_type(operator_class))
    {
        undo_stack.push(new AddCommand(*this, operator_class, x, y));
    }
}


void ProgramModel::remove_operator_undoable(BaseOperator * operator_ptr)
{
    if (operator_ptr) // TODO: check if active
    {
        undo_stack.push(new RemoveCommand(*this, operator_ptr));
    }
}


void ProgramModel::move_operator_undoable(BaseOperator * operator_ptr, int x, int y)
{
    if (operator_ptr)
    {
        int start_x = operator_ptr->get_position_x();
        int start_y = operator_ptr->get_position_y();

        if (x != start_x || y != start_y)
        {
            undo_stack.push(new MoveCommand(*operator_ptr, x, y));
        }
    }
}


void ProgramModel::connect_operators_undoable(QPointer<BaseOperator> operator_a, QPointer<BaseOperator> operator_b, int b_input)
{

}


void ProgramModel::disconnect_operators_undoable(QPointer<BaseOperator> operator_a, QPointer<BaseOperator> operator_b, int b_input)
{

}


BaseOperator* ProgramModel::create_operator(const char* operator_class, int x, int y)
{
    auto op = operator_library.create_operator(operator_class);

    if (op)
    {
        op->set_position(x, y);
    }
    return op;
}


void ProgramModel::add_operator(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        auto blocks = operator_ptr->get_outputs();

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


void ProgramModel::remove_operator(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        operator_ptr->release_resources();

        auto blocks = operator_ptr->get_outputs();

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


QList<BaseOperator*> ProgramModel::get_entry_nodes()
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


QList<BaseOperator*> ProgramModel::get_all_nodes()
{
    return findChildren<BaseOperator*>();
}
