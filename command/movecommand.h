#pragma once

#include <QUndoCommand>

#include "model/BaseOperator.hpp"



class MoveCommand : public QUndoCommand
{

public:

    MoveCommand(BaseOperator& op, int to_x_, int to_y_)
        : operator_(op), to_x(to_x_), to_y(to_y_)
    {
        from_x = op.positionX();
        from_y = op.positionY();
    }

    void redo() override
    {
        operator_.set_position(to_x, to_y);
    }

    void undo() override
    {
        operator_.set_position(from_x, from_y);
    }


private:

    BaseOperator& operator_;
    int from_x, from_y;
    int to_x, to_y;

};
