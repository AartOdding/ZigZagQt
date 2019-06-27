#pragma once

#include <QUndoCommand>

#include "programmodel.h"



class MoveCommand : public QUndoCommand
{

public:

    MoveCommand(ProgramModel& model_, qint64 id, int from_x_, int from_y_, int to_x_, int to_y_)
        : model(model_), operator_id(id), from_x(from_x_), from_y(from_y_), to_x(to_x_), to_y(to_y_)
    { }

    void redo() override
    {
        model.move_operator(operator_id, to_x, to_y);
    }

    void undo() override
    {
        model.move_operator(operator_id, from_x, from_y);
    }


private:

    ProgramModel& model;
    qint64 operator_id;
    int from_x, from_y;
    int to_x, to_y;

};
