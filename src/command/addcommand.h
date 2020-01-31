#pragma once

#include <QUndoCommand>

#include "model/OperatorNetwork.hpp"
#include "model/BaseOperator.hpp"




class AddCommand : public QUndoCommand
{

public:

    AddCommand(OperatorNetwork& mdl, BaseOperator* op)
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

    OperatorNetwork& model;

    BaseOperator* operator_ptr;

    bool has_ownership = true;

};
