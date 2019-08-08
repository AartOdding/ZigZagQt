#include "datablockconnector.h"

#include "model/datablockinput.h"
#include "model/basedatablock.h"

#include "view/projectscopeview.h"
#include "view/operatorview.h"

#include "application.h"

#include <iostream>

#include <QDrag>
#include <QWidget>
#include <QPainter>
#include <QVector2D>
#include <QMimeData>
#include <QGuiApplication>
#include <QGraphicsSceneMouseEvent>




DataBlockConnector::DataBlockConnector(OperatorView& parent, DataBlockInput& input, int h)
    : BaseConnector(application::project_view_model(), static_cast<QGraphicsItem*>(&parent)),
      parent_view(&parent),
      data_input(&input)
{
    int path_height = std::min(h - 6, 25);
    bounds = QRectF(-40, -h/2, 55, h);
    clip_bounds = QRectF(-40, -h/2, 40, h);

    path.addRoundedRect(QRectF(-15, -path_height/2, 20, path_height), 3, 3);
}


DataBlockConnector::DataBlockConnector(OperatorView& parent, BaseDataBlock& output, int h)
    : BaseConnector(application::project_view_model(), static_cast<QGraphicsItem*>(&parent)),
      parent_view(&parent),
      data_output(&output)
{
    int path_height = std::min(h - 4, 25);
    bounds = QRectF(-15, -h/2, 55, h);
    clip_bounds = QRectF(0, -h/2, 40, h);

    path.addRoundedRect(QRectF(-5, -path_height/2, 20, path_height), 3, 3);
}


QRectF DataBlockConnector::boundingRect() const
{
    return bounds;
}


bool DataBlockConnector::can_connect_with(BaseConnector* other) const
{
    auto o = dynamic_cast<DataBlockConnector*>(other);
    if (o && o->is_input() != is_input())
    {
        return true;
    }
    return false;
}


void DataBlockConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setClipRect(clip_bounds);

    auto fill_brush = QBrush(highlighted ? QColor(205, 255, 0) : QColor(55, 55, 55));
    auto stroke_pen = QPen(QBrush(QColor(205, 255, 0)), 2);

    painter->fillPath(path, fill_brush);
    painter->setPen(stroke_pen);
    painter->drawPath(path);
}


void DataBlockConnector::highlight_on_event()
{
    highlighted = true;
    update();
}


void DataBlockConnector::highlight_off_event()
{
    highlighted = false;
    update();
}


void DataBlockConnector::connection_made_event(BaseConnector* other)
{
    auto o = dynamic_cast<DataBlockConnector*>(other);

    if (is_input() && o && o->is_output())
    {
        data_input->connect_to(o->data_output);
    }
}
