#include "view/programview.h"
#include "view/operatorview.h"

#include "model/operator/baseoperator.h"

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
    connect(data_model, &ProgramModel::operator_deleted, this, &ProgramView::on_operator_deleted);
}


void ProgramView::on_operator_added(BaseOperator* pointer, qint64 id)
{
    OperatorView* op = new OperatorView(*data_model, pointer, id);
    operator_views.insert(id, op);
    addItem(op);
}


void ProgramView::on_operator_deleted(qint64 id)
{
    if (operator_views.contains(id))
    {
        OperatorView* op = operator_views[id];
        operator_views.remove(id);
        removeItem(op);
        delete op;
    }
}


void ProgramView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //emit add_operator_signal("shader", mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    data_model->add_operator_undoable("shader", mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
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
