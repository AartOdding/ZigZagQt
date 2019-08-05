#include "projectscopeview.h"
#include "application.h"

#include "view/baseconnector.h"
#include "view/operatorview.h"
#include "view/datablockcable.h"
#include "model/baseoperator.h"
#include "model/datablockinput.h"

#include <QPointer>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

#include <iostream>


ProjectScopeView::ProjectScopeView(QObject *parent)
{
    setBackgroundBrush(QBrush(QColor(55, 55, 55)));
}


void ProjectScopeView::set_model(ProjectModel *model)
{
    data_model = model;

    connect(this, &ProjectScopeView::redo_signal, data_model, &ProjectModel::redo);
    connect(this, &ProjectScopeView::undo_signal, data_model, &ProjectModel::undo);

    connect(data_model, &ProjectModel::operator_added, this, &ProjectScopeView::on_operator_added);
    connect(data_model, &ProjectModel::operator_removed, this, &ProjectScopeView::on_operator_deleted);
}


void ProjectScopeView::bring_to_front(OperatorView* op)
{
    for (auto o : operator_views)
    {
        if (o != op)
        {
            o->setZValue(0.1);
        }
    }
    op->setZValue(1);
}

/*
BaseConnector * ProjectScopeView::connector_at(const QPointF& pos) const
{
    return dynamic_cast<BaseConnector *>(itemAt(pos, QTransform()));
}*/


void ProjectScopeView::on_operator_added(BaseOperator* operator_ptr)
{
    OperatorView* op_view = new OperatorView(*operator_ptr);
    operator_views.insert(operator_ptr, op_view);

    for (auto i : operator_ptr->inputs())
    {
        if (i)
        {
            connect(i, &DataBlockInput::has_connected, this, &ProjectScopeView::on_input_connected);
            connect(i, &DataBlockInput::has_disconnected, this, &ProjectScopeView::on_input_disconnected);
        }
    }

    addItem(op_view);
}


void ProjectScopeView::on_operator_deleted(BaseOperator* operator_ptr)
{
    if (operator_views.contains(operator_ptr))
    {
        for (auto i : operator_ptr->inputs())
        {
            if (i)
            {
                disconnect(i, &DataBlockInput::has_connected, this, &ProjectScopeView::on_input_connected);
                disconnect(i, &DataBlockInput::has_disconnected, this, &ProjectScopeView::on_input_disconnected);
            }
        }

        OperatorView* op_view = operator_views[operator_ptr];
        operator_views.remove(operator_ptr);
        removeItem(op_view);
        delete op_view;
    }
}


void ProjectScopeView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);

    if (!mouseEvent->isAccepted())
    {
        data_model->add_operator("test", mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    }
}


void ProjectScopeView::keyPressEvent(QKeyEvent *keyEvent)
{
    keyEvent->setAccepted(false);
    QGraphicsScene::keyPressEvent(keyEvent);

    if (!keyEvent->isAccepted())
    {
        if (keyEvent->matches(QKeySequence::Undo))
        {
            emit undo_signal();
            keyEvent->setAccepted(true);
        }
        else if (keyEvent->matches(QKeySequence::Redo))
        {
            emit redo_signal();
            keyEvent->setAccepted(true);
        }
        else if (keyEvent->matches(QKeySequence::Delete))
        {
            application::project_model()->get_undo_stack()->beginMacro("Remove selected operators.");

            for (auto obj : selectedItems())
            {
                auto op = dynamic_cast<OperatorView*>(obj);

                if (op)
                {
                    op->operator_model.remove();
                }
            }
            application::project_model()->get_undo_stack()->endMacro();
            keyEvent->setAccepted(true);
        }
        else if (keyEvent->matches(QKeySequence::SelectAll))
        {
            for (auto op : operator_views)
            {
                op->setSelected(true);
            }
            keyEvent->setAccepted(true);
        }
    }
}


void ProjectScopeView::keyReleaseEvent(QKeyEvent *keyEvent)
{
    QGraphicsScene::keyReleaseEvent(keyEvent);
}


void ProjectScopeView::on_input_connected(BaseDataBlock* output, DataBlockInput* input)
{
    auto input_op = operator_views[input->get_parent_operator()];
    auto output_op = operator_views[output->get_parent_operator()];

    if (input_op && output_op)
    {
        auto input_view = input_op->get_view_of(input);
        auto output_view = output_op->get_view_of(output);

        if (input_view && output_view)
        {
            auto cable = new DataBlockCable(this, input_view, output_view);
            cable_views.insert(input_view, cable);
            addItem(cable);
        }
    }
}

void ProjectScopeView::on_input_disconnected(BaseDataBlock* output, DataBlockInput* input)
{
    auto input_op = operator_views[input->get_parent_operator()];

    if (input_op)
    {
        auto input_view = input_op->get_view_of(input);

        if (input_view)
        {
            auto cable = cable_views[input_view];
            cable_views.remove(input_view);
            removeItem(cable);
            delete cable;
        }
    }
}

