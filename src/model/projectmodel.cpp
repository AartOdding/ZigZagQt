#include "projectmodel.h"
#include "application.h"
#include <utility/Serializer.hpp>

#include "model/BaseOperator.hpp"
#include "model/BaseDataType.hpp"
#include "model/datainput.h"

#include "command/addcommand.h"
#include "command/removecommand.h"

#include <QFile>
#include <QString>
#include <QPointer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <iostream>



ProjectModel::ProjectModel()
    : BaseZigZagObject(nullptr, QString())
{ }


QUndoStack* ProjectModel::get_undo_stack()
{
    return &undo_stack;
}


void ProjectModel::redo()
{
    undo_stack.redo();
}


void ProjectModel::undo()
{
    undo_stack.undo();
}


void ProjectModel::add_operator(const OperatorDescription& op_type, int x, int y)
{
    auto op = op_type.construct(this);
    op->set_position(x, y);

    undo_stack.push(new AddCommand(*this, op));
}


void ProjectModel::remove_operator(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        undo_stack.beginMacro("Remove Operator");

        operator_ptr->disconnectParameters();

        for (auto& input : operator_ptr->dataInputs())
        {
            //input->remove_imports_exports();
            input->disconnect();
        }
        for (auto& output : operator_ptr->dataOutputs())
        {
            //output->remove_imports_exports();
            output->disconnectFromAll();
        }
        undo_stack.push(new RemoveCommand(*this, operator_ptr));
        undo_stack.endMacro();
    }
}


void ProjectModel::add_operator_to_model(BaseOperator * operator_ptr)
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

        operators.push_back(operator_ptr);

        context->functions()->glBindFramebuffer(GL_FRAMEBUFFER, old_fbo);
        //context->functions()->glFlush();

        emit operator_added(operator_ptr);

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


void ProjectModel::remove_operator_from_model(BaseOperator * operator_ptr)
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

        operators.erase(std::remove(operators.begin(), operators.end(), operator_ptr), operators.end());
        emit operator_removed(operator_ptr);
    }
}


const std::vector<BaseOperator*>& ProjectModel::all_operators() const
{
    return operators;
}


void ProjectModel::loadState(const QVariantMap&)
{

}



QVariantMap ProjectModel::storeState() const
{

}



void ProjectModel::createChild(const QXmlStreamAttributes&)
{

}


/*
void ProjectModel::saveModel(const QString& path)
{
    QFile file(path);
    file.open(QFile::WriteOnly | QFile::Truncate);
    std::cout << "SAVEEEE\n";
}


void ProjectModel::loadModel(const QString& path)
{

}*/
