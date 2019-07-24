#pragma once

#include <QUndoCommand>

#include "model/programmodel.h"




class AddCommand : public QUndoCommand
{

public:

    AddCommand(ProgramModel& mdl, BaseOperator* op)
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

    ProgramModel& model;

    BaseOperator* operator_ptr;

    bool has_ownership = true;

};
