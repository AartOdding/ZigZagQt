#pragma once

#include <QUndoCommand>

#include "model/program/programmodel.h"




class RemoveCommand : public QUndoCommand
{

public:

    RemoveCommand(ProgramModel& m, BaseOperator * op)
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
            model.remove_operator(operator_ptr);
            has_ownership = true;
        }
    }

    void undo() override
    {
        if (operator_ptr)
        {
            model.add_operator(operator_ptr);
            has_ownership = false;
        }
    }


private:

    ProgramModel& model;

    BaseOperator * operator_ptr;

    bool has_ownership = false;


};
