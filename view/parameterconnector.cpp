#include "parameterconnector.h"
#include "application.h"
#include "operatorview.h"
#include "model/parameter/baseparameter.h"
#include "model/baseoperator.h"

#include <QMenu>
#include <QGraphicsSceneResizeEvent>

#include <iostream>


ParameterConnector::ParameterConnector(OperatorView& op_view, bool is_input)
    : BaseConnector(application::project_view_model()),
      operator_view(&op_view), is_input_(is_input)
{
}


void ParameterConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    auto fill_brush = QBrush(hovered || is_connecting() ? QColor(255, 255, 255) : QColor(55, 55, 55));
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


void ParameterConnector::connection_requested_event(BaseConnector* other)
{
    std::cout << "connection rquested\n";
}


void ParameterConnector::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    auto size = event->newSize();
    int path_height = std::min(size.height() - 4, 18.0);
    double x = is_input() ? 13 : -8;
    double y = 0.5 * (size.height() - path_height);
    path = QPainterPath(); // Clear it
    path.addRoundedRect(QRectF(x, y, 20, path_height), path_height / 3.0, path_height / 3.0);
}


void ParameterConnector::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}


void ParameterConnector::item_selected(QAction *action)
{
    auto par = action->data().value<BaseParameter*>();
    std::cout << par->name() << "\n";
    try_connect();
}


void ParameterConnector::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    auto p = event->pos();

    // Necessary for some bug in qt where events get send to the wrong object :(
    if (p.x() >= 0 && p.y() >= 0 && p.x() <= size().width() && p.y() <= size().height())
    {
        QMenu* menu = new QMenu();
        auto op_menu = menu->addMenu("Operator");
        for (auto p : operator_view->operator_model.parameters())
        {
            op_menu->addAction(p->name())->setData(QVariant::fromValue(p));
        }

        connect(menu, &QMenu::triggered, this, &ParameterConnector::item_selected);
        menu->exec(event->screenPos());
    }
}


void ParameterConnector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}
