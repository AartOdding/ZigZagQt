#include "projectmodel.h"
#include "application.h"

#include "model/baseoperator.h"
#include "model/basedatatype.h"
#include "model/datainput.h"

#include "command/addcommand.h"
#include "command/removecommand.h"

#include <QFile>
#include <QString>
#include <QPointer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <iostream>



ProjectModel::ProjectModel(LibraryModel& library)
    : operator_library(library)
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


void ProjectModel::add_operator(const OperatorTypeInfo& op_type, int x, int y)
{
    auto op = op_type.construct();
    op->set_position(x, y);

    undo_stack.push(new AddCommand(*this, op));
}


void ProjectModel::remove_operator(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        undo_stack.beginMacro("Remove Operator");

        operator_ptr->remove_imports_exports();

        for (auto& input : operator_ptr->data_inputs())
        {
            input->remove_imports_exports();
            input->disconnect();
        }
        for (auto& output : operator_ptr->data_outputs())
        {
            output->remove_imports_exports();
            output->disconnect_all();
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

        auto blocks = operator_ptr->data_outputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->acquire_resources();
            }
        }
        operator_ptr->acquire_resources();

        operators.push_back(operator_ptr);

        context->functions()->glBindFramebuffer(GL_FRAMEBUFFER, old_fbo);
        //context->functions()->glFlush();

        emit operator_added(operator_ptr);

        // To avoid cables being drawn to the wrong until the operator is moved, i suspect, it is because
        // layout has not yet been applied when cable is being made.
        auto x = operator_ptr->get_position_x();
        auto y = operator_ptr->get_position_y();
        operator_ptr->set_position(0, 0);
        operator_ptr->set_position(x, y);
        //emit operator_ptr->position_changed();
        //emit operator_ptr->position_changed(operator_ptr->get_position_x(), operator_ptr->get_position_y()+1);
    }
}


void ProjectModel::remove_operator_from_model(BaseOperator * operator_ptr)
{
    if (operator_ptr)
    {
        operator_ptr->release_resources();

        auto blocks = operator_ptr->data_outputs();

        for (auto& block : blocks)
        {
            if (block)
            {
                block->release_resources();
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


void ProjectModel::save_to_file(const QString& path)
{
    QFile file(path);
    file.open(QFile::WriteOnly | QFile::Truncate);
    std::cout << "SAVEEEE\n";
}


void ProjectModel::load_from_file(const QString& path)
{

}
