#include "programview.h"

#include "view/operatorview.h"
#include "model/baseoperator.h"

#include <QPointer>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

#include <iostream>


ProgramView::ProgramView(QObject *parent)
    : QGraphicsScene(-20000, -20000, 40000, 40000, parent)
{
    setBackgroundBrush(QBrush(QColor(30, 30, 30)));
}


void ProgramView::set_model(ProgramModel *model)
{
    data_model = model;
    connect(this, &ProgramView::redo_signal, data_model, &ProgramModel::redo);
    connect(this, &ProgramView::undo_signal, data_model, &ProgramModel::undo);

    connect(data_model, &ProgramModel::operator_added, this, &ProgramView::on_operator_added);
    connect(data_model, &ProgramModel::operator_removed, this, &ProgramView::on_operator_deleted);
}


void ProgramView::on_operator_added(BaseOperator* operator_ptr)
{
    OperatorView* op_view = new OperatorView(*data_model, *operator_ptr);
    operator_views.insert(operator_ptr, op_view);
    addItem(op_view);
}


void ProgramView::on_operator_deleted(BaseOperator* operator_ptr)
{
    if (operator_views.contains(operator_ptr))
    {
        OperatorView* op = operator_views[operator_ptr];
        operator_views.remove(operator_ptr);
        removeItem(op);
        delete op;
    }
}


void ProgramView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //emit add_operator_signal("shader", mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    data_model->add_operator_undoable("test", mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
}


void ProgramView::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->matches(QKeySequence::Undo))
    {
        emit undo_signal();
    }
    else if (keyEvent->matches(QKeySequence::Redo))
    {
        emit redo_signal();
    }
}
