#pragma once

#include <QUndoCommand>
#include <mutex>

#include "model/BaseOperator.hpp"
#include "model/BaseDataType.hpp"
#include "model/datainput.h"


class ConnectCommand : public QUndoCommand
{

public:

    ConnectCommand(BaseDataType* dataOutput, DataInput* dataInput)
        : m_dataOutput(dataOutput),
          m_initialDataOutput(dataInput->connection),
          m_dataInput(dataInput)
    {

    }

    void redo() override
    {
        if (m_initialDataOutput)
        {
            std::scoped_lock lock
            {
                *m_initialDataOutput->getOperator()->getLock(),
                *m_dataOutput->getOperator()->getLock(),
                *m_dataInput->getOperator()->getLock()
            };
            m_initialDataOutput->removeConnection(m_dataInput);
            m_dataOutput->addConnection(m_dataInput);
            m_dataInput->set_connection(m_dataOutput);  // also removes its old connection;
        }
        else
        {
            std::scoped_lock lock
            {
                *m_dataOutput->getOperator()->getLock(),
                *m_dataInput->getOperator()->getLock()
            };
            m_dataOutput->addConnection(m_dataInput);
            m_dataInput->set_connection(m_dataOutput);  // also removes its old connection;
        }
    }

    void undo() override
    {
        if (m_initialDataOutput)
        {
            std::scoped_lock lock
            {
                *m_initialDataOutput->getOperator()->getLock(),
                *m_dataOutput->getOperator()->getLock(),
                *m_dataInput->getOperator()->getLock()
            };
            m_dataOutput->removeConnection(m_dataInput);
            m_initialDataOutput->addConnection(m_dataInput);
            m_dataInput->set_connection(m_initialDataOutput);
        }
        else
        {
            std::scoped_lock lock
            {
                *m_dataOutput->getOperator()->getLock(),
                *m_dataInput->getOperator()->getLock()
            };
            m_dataOutput->removeConnection(m_dataInput);
            m_dataInput->set_connection(m_initialDataOutput);
        }
    }

private:

    BaseDataType* m_dataOutput;
    BaseDataType* m_initialDataOutput;
    DataInput* m_dataInput;

};
