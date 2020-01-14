#pragma once

#include <QUndoCommand>

#include "model/BaseDataType.hpp"
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
            initial_output->removeConnection(input);
        }
        output->addConnection(input);

        input->set_connection(output);  // also removes its old connection;
    }

    void undo() override
    {
        output->removeConnection(input);

        if (initial_output)
        {
            initial_output->addConnection(input);
        }

        input->set_connection(initial_output);
    }

private:

    BaseDataType* output;
    BaseDataType* initial_output;
    DataInput* input;

};
