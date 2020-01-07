#pragma once

#include <QUndoCommand>

#include "model/BaseDataType.hpp"
#include "model/datainput.h"



class DisconnectCommand : public QUndoCommand
{

public:

    DisconnectCommand(BaseDataType* output_, DataInput* input_)
        : output(output_), input(input_)
    {

    }

    void redo() override
    {
        output->removeConnection(input);
        input->set_connection(nullptr);
    }

    void undo() override
    {
        output->addConnection(input);
        input->set_connection(output);
    }

private:

    BaseDataType* output;
    DataInput* input;

};
