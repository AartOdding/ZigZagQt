#include "parameterconnector.h"
#include "application.h"
#include "operatorview.h"

#include <QGraphicsSceneResizeEvent>



ParameterConnector::ParameterConnector(OperatorView& op_view, bool is_input)
    : BaseConnector(application::project_view_model()),
      operator_view(&op_view), m_is_input(is_input)
{
}


void ParameterConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    auto fill_brush = QBrush(is_highlighted() ? QColor(255, 255, 255) : QColor(55, 55, 55));
    auto stroke_pen = QPen(QBrush(QColor(255, 255, 255)), 2);

    painter->fillPath(path, fill_brush);
    painter->setPen(stroke_pen);
    painter->drawPath(path);
}


bool ParameterConnector::can_connect_with(BaseConnector* other) const
{
    auto o = dynamic_cast<ParameterConnector*>(other);
    if (o && o->is_input() != is_input())
    {
        return true;
    }
    return false;
}


void ParameterConnector::connection_made_event(BaseConnector* other)
{

}


void ParameterConnector::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    /*
    auto size = event->newSize();
    int path_height = std::min(size.height() - 4, 20.0);
    double x = is_input() ? 13 : -8;
    double y = 0.5 * (size.height() - path_height);
    path = QPainterPath(); // Clear it
    path.addEllipse(x, y, 25, path_height);*/

    auto size = event->newSize();
    int path_height = std::min(size.height() - 4, 18.0);
    double x = is_input() ? 13 : -8;
    double y = 0.5 * (size.height() - path_height);
    path = QPainterPath(); // Clear it
    path.addRoundedRect(QRectF(x, y, 20, path_height), path_height / 3.0, path_height / 3.0);
    //path.addEllipse(QPointF(size.width() / 2, size.height() / 2), 8, 8);
}
