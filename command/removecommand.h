#pragma once

#include <QUndoCommand>

#include "model/projectmodel.h"




class RemoveCommand : public QUndoCommand
{

public:

    RemoveCommand(ProjectModel& m, BaseOperator * op)
        : model(m), operator_ptr(op)
    {

    }

    ~RemoveCommand() override
    {
        if (has_ownership)
        {
            delete operator_ptr;
        }
    }

    void redo() override
    {
        if (operator_ptr)
        {
            model.remove_operator_from_model(operator_ptr);
            has_ownership = true;
        }
    }

    void undo() override
    {
        if (operator_ptr)
        {
            model.add_operator_to_model(operator_ptr);
            has_ownership = false;
        }
    }


private:

    ProjectModel& model;

    BaseOperator * operator_ptr;

    bool has_ownership = false;


};
