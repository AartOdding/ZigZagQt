#include <QPainter>
#include <QFocusEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>

#include "operatorview.h"
#include "projectscopeview.h"

#include "model/projectmodel.h"
#include "model/baseoperator.h"
#include "model/basedatablock.h"
#include "model/datablockinput.h"
#include "view/datablockconnector.h"



OperatorView::OperatorView(BaseOperator& op)
    : operator_model(op), name_tag("Test operator number x", this)
{
    setZValue(1);
    setPos(op.get_position_x(), op.get_position_y());

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    on_inputs_modified();
    on_outputs_modified();
    on_parameters_modified();

    connect(&operator_model, &BaseOperator::position_changed, this, &OperatorView::on_operator_moved);
    connect(&operator_model, &BaseOperator::inputs_modified, this, &OperatorView::on_inputs_modified);
    connect(&operator_model, &BaseOperator::outputs_modified, this, &OperatorView::on_outputs_modified);
    connect(&operator_model, &BaseOperator::parameters_modified, this, &OperatorView::on_parameters_modified);

    name_tag.setPos(-width / 2, -height / 2 - 33);
    selection_rect.setRect(0, 0, width + 50, height + 46);
    selection_rect.setPos(- width / 2 - 25, -height / 2 - 35);
    selection_rect.setPen(QPen(QBrush(QColor(51, 153, 255)), 2));
    selection_rect.setBrush(QColor(51, 153, 255, 30));
    selection_rect.setFlag(QGraphicsItem::ItemStacksBehindParent);
}


ProjectScopeView* OperatorView::scope_view()
{
    return dynamic_cast<ProjectScopeView*>(scene());
}


QRectF OperatorView::boundingRect() const
{
    return QRectF(-width / 2, -height / 2, width, height);
}


void OperatorView::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    selection_rect.setVisible(isSelected());

    painter->setRenderHint(QPainter::Antialiasing);
    auto brush = QBrush(QColor(55, 55, 55));
    auto pen = QPen(QBrush(QColor(255, 255, 255)), 2);

    painter->fillRect(-width / 2, -height / 2, width, height, brush);
    painter->setPen(pen);
    painter->drawRoundedRect(-width / 2 + 1, -height / 2 + 1, width -2, height -2, 4, 4);
}


DataBlockConnector* OperatorView::get_view_of(const DataBlockInput* input)
{
    return inputs[input];
}


DataBlockConnector* OperatorView::get_view_of(const BaseDataBlock* output)
{
    return outputs[output];
}


void OperatorView::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    scope_view()->bring_to_front(this);
    QGraphicsItem::mousePressEvent(event);
}


void OperatorView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton))
    {
        auto p = event->scenePos() - event->buttonDownPos(Qt::LeftButton);
        position_x = static_cast<int>(p.x());
        position_y = static_cast<int>(p.y());
        setPos(position_x, position_y);
        emit has_moved();
        was_dragged = true;
    }

    QGraphicsItem::mouseMoveEvent(event);
}


void OperatorView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (was_dragged)
    {
        operator_model.move_to(position_x, position_y);
        //model.move_operator_undoable(&operator_, position_x, position_y);
    }
    was_dragged = false;

    if (event->button() == Qt::LeftButton)
    {
        if (!(event->modifiers() & Qt::ControlModifier) && !(event->modifiers() & Qt::ShiftModifier))
        {
            scope_view()->set_focus_operator(this);
        }
    }

    QGraphicsItem::mouseReleaseEvent(event);
}


void OperatorView::keyPressEvent(QKeyEvent *event)
{
    event->setAccepted(false);
}


void OperatorView::keyReleaseEvent(QKeyEvent *event)
{
    event->setAccepted(false);
}


void OperatorView::on_operator_moved(int to_x, int to_y)
{
    if (to_x != position_x || to_y != position_y)
    {
        position_x = to_x;
        position_y = to_y;
        setPos(position_x, position_y);
        emit has_moved();
    }
}


void OperatorView::on_inputs_modified()
{
    const auto& new_inputs = operator_model.inputs();
    float spacing = height / (new_inputs.size());

    for (auto& [k, v] : inputs)
    {
        // If there are inputs in the view that are no longer in the model:
        if (std::find(new_inputs.begin(), new_inputs.end(), k) == new_inputs.end())
        {
            delete inputs[k];
            inputs.erase(k);
        }
    }

    for (int i = 0; i < new_inputs.size(); ++i)
    {
        int x = -width / 2;
        int y = (-height / 2) + i * spacing + spacing / 2;

        if(inputs.count(new_inputs[i]) > 0)
        {
            inputs[new_inputs[i]]->setPos(x, y);
        }
        else
        {
            auto new_input = new DataBlockConnector(*this, *new_inputs[i], spacing);
            new_input->setPos(x, y);
            inputs[new_inputs[i]] = new_input;
        }
    }
}


void OperatorView::on_outputs_modified()
{
    const auto& new_outputs = operator_model.outputs();
    float spacing = height / (new_outputs.size());

    for (auto& [k, v] : outputs)
    {
        // If there are inputs in the view that are no longer in the model:
        if (std::find(new_outputs.begin(), new_outputs.end(), k) == new_outputs.end())
        {
            delete outputs[k];
            outputs.erase(k);
        }
    }

    for (int i = 0; i < new_outputs.size(); ++i)
    {
        int x = width / 2;
        int y = (-height / 2) + i * spacing + spacing / 2;

        if(outputs.count(new_outputs[i]) > 0)
        {
            outputs[new_outputs[i]]->setPos(x, y);
        }
        else
        {
            auto new_output = new DataBlockConnector(*this, *new_outputs[i], spacing);
            new_output->setPos(x, y);
            outputs[new_outputs[i]] = new_output;
        }
    }
}


void OperatorView::on_parameters_modified()
{
    //std::cout << "on_parameters_modified() called\n";
}
