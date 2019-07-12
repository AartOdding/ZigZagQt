#pragma once

#include <QPointer>
#include <QUndoCommand>

#include "model/program/programmodel.h"
#include "model/operator/shadertop.h"


class DisconnectCommand : public QUndoCommand
{

public:

    DisconnectCommand(QPointer<BaseOperator> op_a, QPointer<BaseOperator> op_b, int b_input_index_)
        : operator_a(op_a), operator_b(op_b), b_input_index(b_input_index_)
    { }

    void redo() override
    {
        /*
        Q_ASSERT(operator_a && operator_b);
        Q_ASSERT(operator_b->get_input(b_input_index) == operator_a);

        operator_b->set_input(b_input_index, nullptr);
        */
    }

    void undo() override
    {
        //operator_b->set_input(b_input_index, operator_a);
    }

private:

    QPointer<BaseOperator> operator_a;
    QPointer<BaseOperator> operator_b;
    int b_input_index;

};
