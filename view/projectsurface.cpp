#include "projectsurface.h"
#include "baseconnector.h"



ProjectSurface::ProjectSurface()
    : QGraphicsScene(-20000, -20000, 40000, 40000)
{

}

void ProjectSurface::start_connecting(BaseConnector* connector)
{
    connection_starter = connector;
}

void ProjectSurface::mouse_movement(const QPointF &scene_pos)
{
    if (connection_starter)
    {
        auto over = dynamic_cast<BaseConnector *>(itemAt(scene_pos, QTransform()));

        // Also executes if over == nullptr.
        if (connection_hover && connection_hover != over)
        {
            connection_hover->on_connection_hover_leave(connection_starter);
            connection_hover = nullptr;
        }

        // If previous if executed connection_hover is always nullptr.
        if (!connection_hover && over && connection_starter != over)
        {
            connection_hover = over;
            connection_hover->on_connection_hover_enter(connection_starter);
        }
    }
}


void ProjectSurface::stop_connecting()
{
    if (connection_starter && connection_hover
            && connection_starter->can_connect_with(connection_hover)
            && connection_hover->can_connect_with(connection_starter))
    {
        connection_starter->on_connection_made(connection_hover);
        connection_hover->on_connection_made(connection_starter);
    }
    else if (connection_starter)
    {
        connection_starter->on_connection_abort();
    }
    connection_starter = nullptr;
    connection_hover = nullptr;
}


bool ProjectSurface::is_making_connection() const
{
    return connection_starter != nullptr;
}


bool ProjectSurface::is_hovering_connector() const
{
    return connection_hover != nullptr;
}
