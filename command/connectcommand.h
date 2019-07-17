#pragma once

#include <QUndoCommand>

#include "model/basedatablock.h"
#include "model/datablockinput.h"



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
        // set output
        input->set_connection(output);
    }

    void undo() override
    {
        // set output
        input->set_connection(initial_output);
    }

private:

    BaseDataBlock* output;
    BaseDataBlock* initial_output;
    DataBlockInput* input;

};
