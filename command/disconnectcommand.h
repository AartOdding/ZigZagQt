#pragma once

#include <QUndoCommand>

#include "model/basedatatype.h"
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
        output->remove_connection(input);
        input->set_connection(nullptr);
    }

    void undo() override
    {
        output->add_connection(input);
        input->set_connection(output);
    }

private:

    BaseDataType* output;
    DataInput* input;

};
