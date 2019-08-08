#include "datablockcable.h"
#include "datablockconnector.h"
#include "operatorview.h"

#include "model/baseoperator.h"

#include <iostream>
#include <algorithm>

#include <QPen>
#include <QPainter>




DataBlockCable::DataBlockCable(ProjectScopeView * p, DataBlockConnector * i, DataBlockConnector * o)
    : program_view(p), input_view(i), output_view(o)
{
    setZValue(0.5);
    setFlag(QGraphicsItem::ItemIsSelectable, false);

    auto p1 = i->scenePos();
    auto p2 = o->scenePos();
    setPos(std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y()));

    auto op1 = i->parent_view;
    auto op2 = o->parent_view;

    connect(op1, &OperatorView::has_moved, this, &DataBlockCable::on_movement);
    connect(op2, &OperatorView::has_moved, this, &DataBlockCable::on_movement);

    build_path();
}


QRectF DataBlockCable::boundingRect() const
{
    return path.boundingRect().marginsAdded({ 3, 3, 3, 3 });
}


bool DataBlockCable::is_flipped() const
{
    QPointF out = output_view->scenePos() + QPointF(15, 0);
    QPointF in = input_view->scenePos() - QPointF(15, 0);

    return in.x() < (out.x() + flip_distance);
}

bool DataBlockCable::contains(const QPointF &point) const
{
    return false;
}

void DataBlockCable::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    auto brush = QBrush({ 205, 255, 0 });
    auto pen = QPen(brush, 2);
    painter->setPen(pen);

    //painter->drawRect(boundingRect().marginsRemoved({1, 1, 1, 1}));

    painter->drawPath(path);

}


void DataBlockCable::on_movement()
{

    QPointF out = output_view->scenePos() + QPointF(15, 0);
    QPointF in = input_view->scenePos() - QPointF(15, 0);

    setPos(std::min(in.x(), out.x()), std::min(in.y(), out.y()));

    prepareGeometryChange();

    build_path();

}

float map(float value, float inMin, float inMax, float outMin, float outMax) {
  return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}


void DataBlockCable::build_path()
{
    QPointF out = output_view->scenePos() + QPointF(15, 0);
    QPointF in = input_view->scenePos() - QPointF(15, 0);

    double w = abs(in.x() - out.x());
    double x_extrude = std::max(w * tension, flip_distance * tension);
    //double y_extrude_ratio = std::clamp(map(abs(w), 100, -100, 0, 1), 0.0f, 1.0f);

    path_in_scene = QPainterPath(out);
    QPointF c1 = out + QPointF(x_extrude, 0.0);
    QPointF c2 = in - QPointF(x_extrude, 0.0);
    path_in_scene.cubicTo(c1, c2, in);

    path = mapFromScene(path_in_scene);
}
