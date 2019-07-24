#include "dataconnectorview.h"

#include "model/datablockinput.h"
#include "model/basedatablock.h"

#include "view/operatorview.h"
#include "view/connectionrequestmimedata.h"

#include <iostream>

#include <QDrag>
#include <QWidget>
#include <QPainter>
#include <QVector2D>
#include <QMimeData>
#include <QGuiApplication>
#include <QGraphicsSceneMouseEvent>




DataConnectorView::DataConnectorView(OperatorView& parent, DataBlockInput& input, int h)
    : QGraphicsItem(static_cast<QGraphicsItem*>(&parent)), parent_view(&parent), data_input(&input)
{
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
    int path_height = std::min(h - 6, 25);
    bounds = QRectF(-40, -h/2, 55, h);
    clip_bounds = QRectF(-40, -h/2, 40, h);

    path.addRoundedRect(QRectF(-15, -path_height/2, 20, path_height), 3, 3);
}

DataConnectorView::DataConnectorView(OperatorView& parent, BaseDataBlock& output, int h)
    : QGraphicsItem(static_cast<QGraphicsItem*>(&parent)), parent_view(&parent), data_output(&output)
{
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
    int path_height = std::min(h - 4, 25);
    bounds = QRectF(-15, -h/2, 55, h);
    clip_bounds = QRectF(0, -h/2, 40, h);

    path.addRoundedRect(QRectF(-5, -path_height/2, 20, path_height), 3, 3);
}


QRectF DataConnectorView::boundingRect() const
{
    return bounds;
}


void DataConnectorView::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setClipRect(clip_bounds);

    auto fill_brush = QBrush(highlighted ? QColor(205, 255, 0) : QColor(55, 55, 55));
    auto stroke_pen = QPen(QBrush(QColor(205, 255, 0)), 2);

    painter->fillPath(path, fill_brush);
    painter->setPen(stroke_pen);
    painter->drawPath(path);
}


void DataConnectorView::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //std::cout << "hover enter\n";
    highlighted = true;
    update();
}


void DataConnectorView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //std::cout << "hover leave\n";
    if (!is_dragging)
    {
        highlighted = false;
        update();
    }
}


void DataConnectorView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //std::cout << "mouse pressed\n";
    is_dragging = false;
}


void DataConnectorView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::MouseButton::LeftButton)
    {
        if (!is_dragging)
        {
            auto start_pos = QVector2D(event->buttonDownPos(Qt::MouseButton::LeftButton));
            auto current_pos = QVector2D(event->pos());

            if ((start_pos - current_pos).lengthSquared() > 600)
            {
                //std::cout << "drag start\n";
                is_dragging = true;
                QDrag *drag = new QDrag(event->widget());
                drag->setMimeData(new ConnectionRequestMimeData(this));
                drag->start();
                //std::cout << "after drag\n";

                // This next part executes after the drag is released.
                is_dragging = false;
                highlighted = false;
                update();
            }
        }
    }
}


void DataConnectorView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //std::cout << "mouse released\n";
    //is_dragging = false;
}


void DataConnectorView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    //std::cout << "drag enter\n";

    auto data = qobject_cast<const ConnectionRequestMimeData*>(event->mimeData());
    if (data)
    {
        if (is_input() != data->source->is_input())
        {
            event->setAccepted(true);
            highlighted = true;
            update();
        }
    }
}


void DataConnectorView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    //std::cout << "drag leave\n";
    if (!is_dragging)
    {
        highlighted = false;
        update();
    }
}

void DataConnectorView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    highlighted = false;
    update();

    auto data = qobject_cast<const ConnectionRequestMimeData*>(event->mimeData());

    if (is_input() && data->source->is_output())
    {
        data_input->connect_to(data->source->data_output);
    }
    if (is_output() && data->source->is_input())
    {
        data_output->connect_to(data->source->data_input);
    }

    //std::cout << "drop\n";
}
