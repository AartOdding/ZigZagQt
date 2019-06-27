#pragma once

#include <QPointer>
#include <QUndoCommand>

#include "programmodel.h"
#include "operator/shadertop.h"



class ConnectCommand : public QUndoCommand
{

public:

    ConnectCommand(QPointer<BaseTOP> op_a, QPointer<BaseTOP> op_b, int b_input_index_)
        : operator_a(op_a), operator_b(op_b), b_input_index(b_input_index_)
    { }

    void redo() override
    {
        Q_ASSERT(operator_a && operator_b);

        initial_connection = operator_b->get_input(b_input_index);
        operator_b->set_input(b_input_index, operator_a);
    }

    void undo() override
    {
        Q_ASSERT(operator_a && operator_b);
        Q_ASSERT(operator_b->get_input(b_input_index) == operator_a);

        operator_b->set_input(b_input_index, initial_connection);
    }

private:

    QPointer<BaseTOP> operator_a;
    QPointer<BaseTOP> operator_b;
    QPointer<BaseTOP> initial_connection;
    int b_input_index;
};
