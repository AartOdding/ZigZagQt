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
QUndoStack* OperatorNetwork::getUndoStack()
{
    return &m_undoStack;
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
        m_undoStack.push(new AddOperatorCommand(this, op));
    }
}


void OperatorNetwork::removeOperator(BaseOperator * operatorPtr)
{
    if (operatorPtr)
    {
        m_undoStack.beginMacro("Remove Operator");

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
        m_undoStack.push(new RemoveOperatorCommand(this, operatorPtr));
        m_undoStack.endMacro();
    }
}


// TODO: list might contain dangling pointers
void OperatorNetwork::removeOperators(QList<BaseOperator*> operatorPtrs)
{
    m_undoStack.beginMacro("Remove Operators");

    for (auto op : operatorPtrs)
    {
        removeOperator(op);
    }
    m_undoStack.endMacro();
}


void OperatorNetwork::redo()
{
    m_undoStack.redo();
}


void OperatorNetwork::undo()
{
    m_undoStack.undo();
}


void OperatorNetwork::addOperatorImplementation(BaseOperator * operatorPtr)
{
    if (operatorPtr)
    {
        auto context = QOpenGLContext::currentContext();

        std::cout << "default fbo: " << context->defaultFramebufferObject() << std::endl;

        GLint old_fbo;
        context->functions()->glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &old_fbo);

        std::cout << "was bound fbo: " << old_fbo << std::endl;

        auto blocks = operatorPtr->dataOutputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->acquireResources();
            }
        }
        operatorPtr->acquireResources();

        m_operators.push_back(operatorPtr);

        context->functions()->glBindFramebuffer(GL_FRAMEBUFFER, old_fbo);
        //context->functions()->glFlush();

        emit operatorAdded(QPointer(operatorPtr), operatorPtr->getLock());

        // To avoid cables being drawn to the wrong until the operator is moved, i suspect, it is because
        // layout has not yet been applied when cable is being made.
        auto x = operatorPtr->positionX();
        auto y = operatorPtr->positionY();
        operatorPtr->set_position(0, 0);
        operatorPtr->set_position(x, y);
        //emit operator_ptr->position_changed();
        //emit operator_ptr->position_changed(operator_ptr->get_position_x(), operator_ptr->get_position_y()+1);

        //Serializer serializer;
        //serializer.serialize(operatorPtr);
        //std::cout << serializer.text.toStdString() << std::endl;
    }
}


void OperatorNetwork::removeOperatorImplementation(BaseOperator * operatorPtr)
{
    if (operatorPtr)
    {
        operatorPtr->releaseResources();

        auto blocks = operatorPtr->dataOutputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->releaseResources();
            }
        }

        m_operators.erase(std::remove(m_operators.begin(), m_operators.end(), operatorPtr), m_operators.end());
        emit operatorRemoved(operatorPtr);
    }
}


//-------------------------------------------------------------------------------------

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


//-------------------------------------------------------------------------------------

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
