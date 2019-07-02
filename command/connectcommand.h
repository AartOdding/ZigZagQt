#pragma once

#include <QPointer>
#include <QUndoCommand>

#include "model/program/programmodel.h"
#include "model/operator/shadertop.h"



class ConnectCommand : public QUndoCommand
{

public:

    ConnectCommand(QPointer<BaseOperator> op_a, QPointer<BaseOperator> op_b, int b_input_index_)
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

    QPointer<BaseOperator> operator_a;
    QPointer<BaseOperator> operator_b;
    QPointer<BaseOperator> initial_connection;
    int b_input_index;
};
