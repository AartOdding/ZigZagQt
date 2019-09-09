#include "dataconnector.h"

#include "model/datainput.h"
#include "model/basedatatype.h"

#include "view/projectscopeview.h"
#include "view/operatorview.h"

#include "application.h"

#include <iostream>

#include <QDrag>
#include <QWidget>
#include <QPainter>
#include <QVector2D>
#include <QGuiApplication>
#include <QGraphicsSceneMouseEvent>




DataConnector::DataConnector(OperatorView& op_view, DataInput& input)
    : BaseConnector(application::project_view_model(), &op_view), data_input(&input)
{
    color = input.type()->gui_color;
    visible_width = 15;
}


DataConnector::DataConnector(OperatorView& op_view, BaseDataType& output)
    : BaseConnector(application::project_view_model(), &op_view), data_output(&output)
{
    color = output.type()->gui_color;
    visible_width = 15;
}


void DataConnector::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    auto size = event->newSize();
    int path_height = std::min(size.height() - 4, 25.0);
    double x = is_input() ? 10 : -10;
    double y = 0.5 * (size.height() - path_height);
    path = QPainterPath(); // Clear it
    //path.addRoundedRect(QRectF(x, y, 20, path_height), 4, 4);
    path.addRoundedRect(QRectF(x, y, 25, path_height), path_height / 3.0, path_height / 3.0);
}


bool DataConnector::can_connect_with(BaseConnector* other) const
{
    auto o = dynamic_cast<DataConnector*>(other);
    if (o && o->is_input() != is_input())
    {
        return true;
    }
    return false;
}


void DataConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    auto fill_brush = QBrush(hovered || is_connecting() ? color : QColor(55, 55, 55));
    auto stroke_pen = QPen(QBrush(color), 2);

    painter->fillPath(path, fill_brush);
    painter->setPen(stroke_pen);
    painter->drawPath(path);
}


bool DataConnector::connection_requested_event(BaseConnector* other)
{
    std::cout << "connection requested\n";
    auto o = dynamic_cast<DataConnector*>(other);

    if (o && is_input() != o->is_input())
    {
        if (is_input())
        {
            data_input->connect_to(o->data_output);
        }
        else
        {
            data_output->connect_to(o->data_input);
        }
        return true;
    }
    return false;
}


QColor DataConnector::get_color() const
{
    return color;
}
