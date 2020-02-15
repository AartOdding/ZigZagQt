#pragma once

#include <QUndoCommand>
#include <mutex>

#include "model/BaseOperator.hpp"
#include "model/BaseDataType.hpp"
#include "model/datainput.h"



class DisconnectCommand : public QUndoCommand
{

public:

    DisconnectCommand(BaseDataType* output_, DataInput* input_)
        : output(output_),
          input(input_)
    {

    }

    void redo() override
    {
        std::scoped_lock lock
        {
            *output->getOperator()->getLock(),
            *input->getOperator()->getLock()
        };
        output->removeConnection(input);
        input->set_connection(nullptr);
    }

    void undo() override
    {
        std::scoped_lock lock
        {
            *output->getOperator()->getLock(),
            *input->getOperator()->getLock()
        };
        output->addConnection(input);
        input->set_connection(output);
    }

private:

    BaseDataType* output;
    DataInput* input;

};
