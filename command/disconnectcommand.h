#pragma once

#include <QPointer>
#include <QUndoCommand>

#include "model/programmodel.h"
#include "model/baseoperator.h"


class DisconnectCommand : public QUndoCommand
{

public:

    DisconnectCommand(BaseDataBlock* output_, DataBlockInput* input_)
        : output(output_), input(input_)
    {

    }

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

    BaseDataBlock* output;
    DataBlockInput* input;

};
