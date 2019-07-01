#include "model/programmodel.h"
#include "model/operator/baseoperator.h"

#include "command/addcommand.h"
#include "command/removecommand.h"
#include "command/connectcommand.h"
#include "command/disconnectcommand.h"
#include "command/movecommand.h"

#include <QString>
#include <QPointer>

#include <iostream>




ProgramModel::ProgramModel()
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


void ProgramModel::add_operator_undoable(const QString& operator_class, int x, int y)
{
    // TODO: check if class exists, else do not push command on stack
    undo_stack.push(new AddCommand(*this, operator_class, x, y));
}


void ProgramModel::remove_operator_undoable(QPointer<BaseOperator> operator_)
{
    std::cout << "Remove command not yet supported\n";
    //undo_stack.push(new RemoveCommand(*this, operator_));
}


void ProgramModel::move_operator_undoable(qint64 id, int x, int y)
{
    if (operators.contains(id))
    {
        auto op = operators[id];
        int start_x = op->get_position_x();
        int start_y = op->get_position_y();

        if (x != start_x || y != start_y)
        {
            undo_stack.push(new MoveCommand(*this, id, start_x, start_y, x, y));
        }
    }
}


void ProgramModel::connect_operators_undoable(QPointer<BaseOperator> operator_a, QPointer<BaseOperator> operator_b, int b_input)
{

}


void ProgramModel::disconnect_operators_undoable(QPointer<BaseOperator> operator_a, QPointer<BaseOperator> operator_b, int b_input)
{

}


void ProgramModel::add_operator(const QString& operator_class, int x, int y, qint64 id)
{
    if (name_manager.is_valid(id) && !operators.contains(id))
    {
        QPointer<BaseOperator> new_operator = new ShaderTOP(*this);
        operators.insert(id, new_operator);
        emit operator_added(new_operator, id);
        new_operator->set_position(x, y);
        new_operator->set_num_inputs(qrand() % 6);
    }
}

void ProgramModel::delete_operator(qint64 id)
{
    if (operators.contains(id))
    {
        auto op = operators[id];
        operators.remove(id);
        delete op;
        emit operator_deleted(id);
    }
}

void ProgramModel::move_operator(qint64 id, int to_x, int to_y)
{
    if (operators.contains(id))
    {
        auto op = operators[id];
        int start_x = op->get_position_x();
        int start_y = op->get_position_y();

        if (to_x != start_x || to_y != start_y)
        {
            operators[id]->set_position(to_x, to_y);
        }
    }
}


QList<BaseOperator*> ProgramModel::get_entry_nodes()
{
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
}


QList<BaseOperator*> ProgramModel::get_all_nodes()
{
    return findChildren<BaseOperator*>();
}
