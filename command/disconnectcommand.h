#pragma once

#include <QUndoCommand>

#include "model/basedatablock.h"
#include "model/datablockinput.h"


class DisconnectCommand : public QUndoCommand
{

public:

    DisconnectCommand(BaseDataBlock* output_, DataBlockInput* input_)
        : output(output_), input(input_)
    {

    }

    void redo() override
    {
        input->set_connection(nullptr);
    }

    void undo() override
    {
        //operator_b->set_input(b_input_index, operator_a);
        input->set_connection(output);
    }

private:

    BaseDataBlock* output;
    DataBlockInput* input;

};
