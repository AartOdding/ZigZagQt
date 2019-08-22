#pragma once

#include <QUndoCommand>

#include "model/basedatatype.h"
#include "model/datainput.h"



class ConnectCommand : public QUndoCommand
{

public:

    ConnectCommand(BaseDataType* output_, DataInput* input_)
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

    BaseDataType* output;
    BaseDataType* initial_output;
    DataInput* input;

};
