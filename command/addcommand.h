#pragma once

#include <QUndoCommand>

#include "model/projectmodel.h"
#include "model/baseoperator.h"




class AddCommand : public QUndoCommand
{

public:

    AddCommand(ProjectModel& mdl, BaseOperator* op)
        : model(mdl), operator_ptr(op)
    {
    }

    ~AddCommand() override
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
            model.add_operator_to_model(operator_ptr);
            has_ownership = false;
        }
    }

    void undo() override
    {
        if (operator_ptr)
        {
            model.remove_operator_from_model(operator_ptr);
            has_ownership = true;
        }
    }


private:

    ProjectModel& model;

    BaseOperator* operator_ptr;

    bool has_ownership = true;

};
