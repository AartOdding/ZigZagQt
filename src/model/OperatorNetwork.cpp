#include "OperatorNetwork.hpp"
#include "application.h"
#include <utility/Serializer.hpp>

#include "model/BaseOperator.hpp"
#include "model/BaseDataType.hpp"
#include "model/datainput.h"

#include <QFile>
#include <QString>
#include <QPointer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QMetaMethod>

#include <iostream>



OperatorNetwork::OperatorNetwork(const QString& name)
    : BaseZigZagObject(nullptr, name)
{

}


const std::vector<BaseOperator*>& OperatorNetwork::getOperators() const
{
    return m_operators;
}


// TODO: move elsewhere
QUndoStack* OperatorNetwork::get_undo_stack()
{
    return &undo_stack;
}


void OperatorNetwork::loadState(const QVariantMap&)
{

}


QVariantMap OperatorNetwork::storeState() const
{
    return QVariantMap();
}



void OperatorNetwork::createChild(const QXmlStreamAttributes&)
{

}


void OperatorNetwork::addOperator(const OperatorDescription* operatorDescription, int xPos, int yPos)
{
    if (operatorDescription)
    {
        BaseOperator* op = operatorDescription->construct(this);
        op->set_position(xPos, yPos);
        undo_stack.push(new AddOperatorCommand(this, op));
    }
}


void OperatorNetwork::removeOperator(BaseOperator * operatorPtr)
{
    if (operatorPtr)
    {
        undo_stack.beginMacro("Remove Operator");

        operatorPtr->disconnectParameters();

        for (auto& input : operatorPtr->dataInputs())
        {
            //input->remove_imports_exports();
            input->disconnect();
        }
        for (auto& output : operatorPtr->dataOutputs())
        {
            //output->remove_imports_exports();
            output->disconnectFromAll();
        }
        undo_stack.push(new RemoveOperatorCommand(this, operatorPtr));
        undo_stack.endMacro();
    }
}


void OperatorNetwork::removeOperators(QList<BaseOperator*> operatorPtrs)
{
    undo_stack.beginMacro("Remove Operators");

    for (auto op : operatorPtrs)
    {
        removeOperator(op);
    }
    undo_stack.endMacro();
}


void OperatorNetwork::redo()
{
    undo_stack.redo();
}


void OperatorNetwork::undo()
{
    undo_stack.undo();
}


void OperatorNetwork::addOperatorImplementation(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        auto context = QOpenGLContext::currentContext();
        GLint old_fbo;
        context->functions()->glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &old_fbo);

        auto blocks = operator_ptr->dataOutputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->acquireResources();
            }
        }
        operator_ptr->acquire_resources();

        m_operators.push_back(operator_ptr);

        context->functions()->glBindFramebuffer(GL_FRAMEBUFFER, old_fbo);
        //context->functions()->glFlush();

        emit operatorAdded(operator_ptr);

        // To avoid cables being drawn to the wrong until the operator is moved, i suspect, it is because
        // layout has not yet been applied when cable is being made.
        auto x = operator_ptr->positionX();
        auto y = operator_ptr->positionY();
        operator_ptr->set_position(0, 0);
        operator_ptr->set_position(x, y);
        //emit operator_ptr->position_changed();
        //emit operator_ptr->position_changed(operator_ptr->get_position_x(), operator_ptr->get_position_y()+1);

        Serializer serializer;
        serializer.serialize(operator_ptr);
        std::cout << serializer.text.toStdString() << std::endl;
    }
}


void OperatorNetwork::removeOperatorImplementation(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        operator_ptr->release_resources();

        auto blocks = operator_ptr->dataOutputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->releaseResources();
            }
        }

        m_operators.erase(std::remove(m_operators.begin(), m_operators.end(), operator_ptr), m_operators.end());
        emit operatorRemoved(operator_ptr);
    }
}


OperatorNetwork::AddOperatorCommand::AddOperatorCommand(OperatorNetwork* network, BaseOperator* op)
    : m_network(network),
      m_operator(op),
      m_hasOwnership(true)
{

}


OperatorNetwork::AddOperatorCommand::~AddOperatorCommand()
{
    if (m_network && m_operator && m_hasOwnership)
    {
        delete m_operator;
    }
}


void OperatorNetwork::AddOperatorCommand::redo()
{
    if (m_network && m_operator)
    {
        m_network->addOperatorImplementation(m_operator);
        m_hasOwnership = false;
    }
}


void OperatorNetwork::AddOperatorCommand::undo()
{
    if (m_network && m_operator)
    {
        m_network->removeOperatorImplementation(m_operator);
        m_hasOwnership = true;
    }
}


OperatorNetwork::RemoveOperatorCommand::RemoveOperatorCommand(OperatorNetwork* network, BaseOperator* op)
    : m_network(network),
      m_operator(op),
      m_hasOwnership(true)
{

}


OperatorNetwork::RemoveOperatorCommand::~RemoveOperatorCommand()
{
    if (m_network && m_operator && m_hasOwnership)
    {
        delete m_operator;
    }
}


void OperatorNetwork::RemoveOperatorCommand::redo()
{
    if (m_network && m_operator)
    {
        m_network->removeOperatorImplementation(m_operator);
        m_hasOwnership = true;
    }
}


void OperatorNetwork::RemoveOperatorCommand::undo()
{
    if (m_network && m_operator)
    {
        m_network->addOperatorImplementation(m_operator);
        m_hasOwnership = false;
    }
}
