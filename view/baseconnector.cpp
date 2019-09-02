#include "application.h"
#include "baseconnector.h"
#include "projectsurface.h"

#include <QVector2D>
#include <QGraphicsSceneMouseEvent>

#include <iostream>


BaseConnector::BaseConnector(ProjectSurface* surface_, QGraphicsItem* parent_)
    : QGraphicsWidget(parent_), surface(surface_)
{
    setFlag(QGraphicsItem::ItemClipsToShape); // Enable clipping.
    setFlag(QGraphicsItem::ItemIsFocusable); // Because we need focus out event.
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setMinimumSize(10, 10);
    setPreferredSize(10, 10);
}


bool BaseConnector::is_connecting() const
{
    return surface->connection_starter == this;
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


void BaseConnector::focusOutEvent(QFocusEvent *event)
{
    if (!surface->is_hovering_connector())
    {
        surface->stop_connecting();
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
    if (!surface->is_making_connection())
    {
        auto start_pos = QVector2D(event->buttonDownPos(Qt::MouseButton::LeftButton));
        auto current_pos = QVector2D(event->pos());

        if ((start_pos - current_pos).lengthSquared() > 400)
        {
            surface->start_connecting(this);
        }
    }
}


void BaseConnector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (surface->is_making_connection())
    {
        surface->stop_connecting();
    }
    else
    {
        surface->start_connecting(this);
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
