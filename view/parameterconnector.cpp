#include "parameterconnector.h"
#include "application.h"
#include "operatorview.h"
#include "model/parameter/BaseParameter.hpp"
#include "model/baseoperator.h"
#include "model/datainput.h"
#include "model/basedatatype.h"
#include "view/projectscopeview.h"

#include <QMenu>
#include <QGraphicsSceneResizeEvent>

#include <iostream>


ParameterConnector::ParameterConnector(OperatorView& op_view, bool is_input)
    : BaseConnector(application::project_view_model(), &op_view), is_input_(is_input)
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


bool ParameterConnector::connection_requested_event(BaseConnector* other)
{
    auto o = dynamic_cast<ParameterConnector*>(other);

    if (o && is_input() != o->is_input())
    {
        if (is_input())
        {
            int num_components = std::min(last_selected_parameter->getComponents().size(), o->last_selected_parameter->getComponents().size());
            for (int i = 0; i < num_components; ++i)
            {
                last_selected_parameter->getComponents()[i]->startImporting(o->last_selected_parameter->getComponents()[i]);
            }
            return true;
        }
        else
        {
            int num_components = std::min(last_selected_parameter->getComponents().size(), o->last_selected_parameter->getComponents().size());
            for (int i = 0; i < num_components; ++i)
            {
                o->last_selected_parameter->getComponents()[i]->startImporting(last_selected_parameter->getComponents()[i]);
            }
            return true;
        }
    }
    return false;
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
    Q_ASSERT(par);
    last_selected_parameter = par;
    try_connect();
}


void ParameterConnector::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    auto p = event->pos();

    // Necessary for some bug in qt where events get send to the wrong object :(
    if (p.x() >= 0 && p.y() >= 0 && p.x() <= size().width() && p.y() <= size().height())
    {
        QMenu* menu = new QMenu();

        auto op_menu = menu->addMenu(operator_view()->operator_model.type()->name.c_str());

        for (auto par : operator_view()->operator_model.findChildren<BaseParameter*>(QString(), Qt::FindDirectChildrenOnly))
        {
            op_menu->addAction(par->objectName())->setData(QVariant::fromValue(par));
        }

        for (auto output : operator_view()->operator_model.data_outputs())
        {
            if (output->findChildren<BaseParameter*>().size() > 0)
            {
                auto output_menu = menu->addMenu(output->objectName());

                for (auto par : output->findChildren<BaseParameter*>(QString(), Qt::FindDirectChildrenOnly))
                {
                    output_menu->addAction(par->objectName())->setData(QVariant::fromValue(par));
                }
            }
        }

        for (auto input : operator_view()->operator_model.data_inputs())
        {
            if (input->findChildren<BaseParameter*>().size() > 0)
            {
                auto input_menu = menu->addMenu(input->objectName());

                for (auto par : input->findChildren<BaseParameter*>(QString(), Qt::FindDirectChildrenOnly))
                {
                    input_menu->addAction(par->objectName())->setData(QVariant::fromValue(par));
                }
            }
        }

        connect(menu, &QMenu::triggered, this, &ParameterConnector::item_selected);
        menu->exec(event->screenPos());
    }
}


void ParameterConnector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}
