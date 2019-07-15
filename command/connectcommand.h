#pragma once

#include <QPointer>
#include <QUndoCommand>

#include "model/programmodel.h"



class ConnectCommand : public QUndoCommand
{

public:

    ConnectCommand(BaseDataBlock* output_, DataBlockInput* input_)
        : output(output_), input(input_)
    {
        initial_output; // = input get connection whatever
    }

    void redo() override
    {
        /*
        Q_ASSERT(operator_a && operator_b);

        initial_connection = operator_b->get_input(b_input_index);
        operator_b->set_input(b_input_index, operator_a);
        */
    }

    void undo() override
    {
        /*
        Q_ASSERT(operator_a && operator_b);
        Q_ASSERT(operator_b->get_input(b_input_index) == operator_a);

        operator_b->set_input(b_input_index, initial_connection);
        */
    }

private:

    BaseDataBlock* output;
    BaseDataBlock* initial_output;
    DataBlockInput* input;

};
