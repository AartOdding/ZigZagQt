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
        initial_output = input->connection;
    }

    void redo() override
    {
        if (initial_output)
        {
            initial_output->remove_connection(input);
        }
        output->add_connection(input);

        input->set_connection(output);  // also removes its old connection;
    }

    void undo() override
    {
        output->remove_connection(input);

        if (initial_output)
        {
            initial_output->add_connection(input);
        }

        input->set_connection(initial_output);
    }

private:

    BaseDataBlock* output;
    BaseDataBlock* initial_output;
    DataBlockInput* input;

};
