#include "projectsurface.h"
#include "baseconnector.h"

#include "operatorview.h"


ProjectSurface::ProjectSurface()
    : QGraphicsScene(-20000, -20000, 40000, 40000)
{

}


void ProjectSurface::start_connecting(BaseConnector* connector)
{
    if (connector && connection_starter && connection_starter != connector)
    {
        stop_connecting();
    }
    if (connection_starter != connector)
    {
        connection_starter = connector;
        connector->set_highlighted(true);
    }
}


void ProjectSurface::mouse_movement(const QPointF &scene_pos)
{
    if (connection_starter)
    {
        auto over = dynamic_cast<BaseConnector *>(itemAt(scene_pos, QTransform()));

        // Also executes if over == nullptr.
        if (connection_hover && connection_hover != over)
        {
            connection_hover->set_highlighted(false);
            connection_hover = nullptr;
        }

        // If previous if executed connection_hover is always nullptr.
        if (!connection_hover && over && connection_starter != over)
        {
            connection_hover = over;

            if (over->can_connect_with(connection_starter)
                && connection_starter->can_connect_with(over))
            {
                connection_hover->set_highlighted(true);
            }
        }
    }
}


void ProjectSurface::stop_connecting()
{
    if (connection_starter && connection_hover
            && connection_starter->can_connect_with(connection_hover)
            && connection_hover->can_connect_with(connection_starter))
    {
        connection_starter->set_highlighted(false);
        connection_hover->set_highlighted(false);
        connection_starter->connection_made_event(connection_hover);
        connection_hover->connection_made_event(connection_starter);
    }
    else if (connection_starter)
    {
        connection_starter->set_highlighted(false);
        connection_starter->connection_aborted_event();
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


void ProjectSurface::set_focus_operator(OperatorView* op)
{
    if (op != focus_operator)
    {
        focus_operator = op;
        emit focus_operator_changed(op ? &op->operator_model : nullptr);
    }
}
