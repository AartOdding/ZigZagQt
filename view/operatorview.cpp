#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>

#include <iostream>

#include "view/operatorview.h"
#include "model/program/programmodel.h"
#include "model/operator/baseoperator.h"



OperatorView::OperatorView(ProgramModel& m, BaseOperator* pointer, qint64 id)
    : model(m), operator_pointer(pointer), operator_id(id), output_connector(*this, pointer, 0, false)
{
    output_connector.setPos(width / 2 - 2, 0);
    connect(pointer, &BaseOperator::position_changed, this, &OperatorView::on_operator_moved);
    connect(pointer, &BaseOperator::num_inputs_changed, this, &OperatorView::on_num_inputs_changed);
}


QRectF OperatorView::boundingRect() const
{
    return QRectF(-width / 2, -height / 2, width, height);
}


void OperatorView::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    auto brush = QBrush(QColor(200, 50, 50));
    painter->fillRect(-width / 2, -height / 2, width, height, brush);
}


void OperatorView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton))
    {
        auto p = event->scenePos() - event->buttonDownPos(Qt::LeftButton);
        position_x = static_cast<int>(p.x());
        position_y = static_cast<int>(p.y());
        setPos(position_x, position_y);
        was_dragged = true;
    }
}


void OperatorView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (was_dragged && operator_pointer)
    {
        model.move_operator_undoable(operator_id, position_x, position_y);
    }
    was_dragged = false;
}


void OperatorView::on_operator_moved(int to_x, int to_y)
{
    if (to_x != position_x || to_y != position_y)
    {
        position_x = to_x;
        position_y = to_y;
        setPos(position_x, position_y);
    }
}

void OperatorView::on_num_inputs_changed(int new_num_inputs)
{
    std::cout << "num inputs changed\n";

    float spacing = width / (new_num_inputs + 3.0f);
    float y = -width / 2 + spacing;

    input_connectors.clear();
    input_connectors.reserve(new_num_inputs);

    for (int i = 0; i < new_num_inputs; ++i)
    {
        y += spacing;
        input_connectors.push_back(new ConnectorView(*this, operator_pointer, i, true));
        input_connectors.back()->setPos(-width/ 2 + 2, y);
    }
}

