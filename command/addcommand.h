#pragma once

#include <QUndoCommand>

#include "model/programmodel.h"




class AddCommand : public QUndoCommand
{

public:

    AddCommand(ProgramModel& model_, const char * operator_class, int x, int y)
        : model(model_)
    {
        operator_ptr = model.create_operator(operator_class, x, y);
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
