#include "cable.h"
#include "DataConnector.hpp"
#include "operatorview.h"

#include "model/baseoperator.h"

#include <iostream>
#include <algorithm>

#include <QPen>
#include <QPainter>




Cable::Cable(ProjectScopeView * p, BaseConnector * out, BaseConnector * in)
    : program_view(p), output_connector(out), input_connector(in)
{
    setZValue(0.5);
    setFlag(QGraphicsItem::ItemIsSelectable, false);

    auto out_pos = output_connector->scenePos();
    auto in_pos = input_connector->scenePos();
    setPos(std::min(out_pos.x(), in_pos.x()), std::min(out_pos.y(), in_pos.y()));

    auto out_op = output_connector->getOperatorView();
    auto in_op = input_connector->getOperatorView();

    connect(out_op, &OperatorView::has_moved, this, &Cable::on_movement);
    connect(in_op, &OperatorView::has_moved, this, &Cable::on_movement);
    connect(output_connector, &QGraphicsWidget::geometryChanged, this, &Cable::on_movement);
    connect(input_connector, &QGraphicsWidget::geometryChanged, this, &Cable::on_movement);

    DataConnector * dataConnector = dynamic_cast<DataConnector*>(output_connector);
    if (dataConnector)
    {
        color = dataConnector->getColor();
    }
    else
    {
        color = Qt::white;
    }

    build_path();
}


QRectF Cable::boundingRect() const
{
    return path.boundingRect().marginsAdded({ 3, 3, 3, 3 });
}


bool Cable::is_flipped() const
{
    QPointF out = output_connector->scenePos() + QPointF(15, 0);
    QPointF in = input_connector->scenePos() - QPointF(15, 0);

    return in.x() < (out.x() + flip_distance);
}


bool Cable::contains(const QPointF &point) const
{
    return false;
}


void Cable::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    auto brush = QBrush(color);
    auto pen = QPen(brush, 2);

    painter->setPen(pen);
    painter->drawPath(path);
}


void Cable::on_movement()
{
    QPointF out = output_connector->scenePos() + QPointF(15, 0);
    QPointF in = input_connector->scenePos() - QPointF(15, 0);
    setPos(std::min(in.x(), out.x()), std::min(in.y(), out.y()));
    prepareGeometryChange();
    build_path();
}


float map(float value, float inMin, float inMax, float outMin, float outMax)
{
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}


void Cable::build_path()
{
    QSizeF halfIn = input_connector->size() / 2;
    QSizeF halfOut = output_connector->size() / 2;

    QPointF in = input_connector->scenePos() + QPointF(halfIn.width(), halfIn.height());
    QPointF out = output_connector->scenePos() + QPointF(halfOut.width(), halfOut.height());

    double w = abs(in.x() - out.x());
    double x_extrude = std::max(w * tension, flip_distance * tension);
    //double y_extrude_ratio = std::clamp(map(abs(w), 100, -100, 0, 1), 0.0f, 1.0f);

    path_in_scene = QPainterPath(out);
    QPointF c1 = out + QPointF(x_extrude, 0.0);
    QPointF c2 = in - QPointF(x_extrude, 0.0);
    path_in_scene.cubicTo(c1, c2, in);

    path = mapFromScene(path_in_scene);
}
