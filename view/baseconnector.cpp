#include "application.h"
#include "baseconnector.h"
#include "connectionmanager.h"

#include <QVector2D>
#include <QGraphicsSceneMouseEvent>

#include <iostream>



BaseConnector::BaseConnector(ConnectionManager* manager_, QGraphicsItem* parent_)
    : QGraphicsWidget(parent_), manager(manager_)
{
    setFlag(QGraphicsItem::ItemClipsToShape); // Enable clipping.
    setFlag(QGraphicsItem::ItemIsFocusable); // Because we need focus out event.
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setMinimumSize(10, 10);
    setPreferredSize(10, 10);
}


void BaseConnector::try_connect()
{
    manager->try_connect(this);
}


bool BaseConnector::is_connecting() const
{
    return manager->active_connector() == this;
}




/*
void BaseConnector::grabMouseEvent(QEvent *event)
{

}*/

/*
void BaseConnector::ungrabMouseEvent(QEvent *event)
{
    if (!surface->is_hovering_connector())
    {
        surface->stop_connecting();
    }
    std::cout << "ungrab\n";
}*/

/*
void BaseConnector::focusOutEvent(QFocusEvent *event)
{
    if (!manager->is_hovering_connector())
    {
        manager->cancel_connection();
    }
}


void BaseConnector::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    set_highlighted(true);
}


void BaseConnector::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!is_connecting())
    {
        set_highlighted(false);
    }
}


void BaseConnector::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!manager->is_connecting())
    {
        auto start_pos = QVector2D(event->buttonDownPos(Qt::MouseButton::LeftButton));
        auto current_pos = QVector2D(event->pos());

        if ((start_pos - current_pos).lengthSquared() > 400)
        {
            manager->try_connect(this);
        }
    }
}


void BaseConnector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (manager->is_connecting())
    {
        manager->cancel_connection();
    }
    else
    {
        manager->try_connect(this);
    }
}


void BaseConnector::set_highlighted(bool highlighted_)
{
    if (highlighted != highlighted_)
    {
        highlighted = highlighted_;
        update();
    }
}
*/
