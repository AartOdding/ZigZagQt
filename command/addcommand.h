#pragma once

#include <QString>
#include <QUndoCommand>

#include "model/program/programmodel.h"



class AddCommand : public QUndoCommand
{

public:

    AddCommand(ProgramModel& model_, const QString& operator_class_, int x, int y)
        : model(model_), operator_class(operator_class_), position_x(x), position_y(y)
    {
        operator_id = model.name_manager.unique_id();
    }

    void redo() override
    {
        model.add_operator(operator_class, position_x, position_y, operator_id);
    }

    void undo() override
    {
        model.delete_operator(operator_id);
    }


private:

    ProgramModel& model;
    QString operator_class;
    qint64 operator_id;
    int position_x;
    int position_y;

};
