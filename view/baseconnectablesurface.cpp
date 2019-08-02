#include "baseconnectablesurface.h"
#include "baseconnectable.h"

#include <QGraphicsSceneMouseEvent>




void BaseConnectableSurface::start_connection(BaseConnectable* connector)
{
    connection_starter = connector;
}

void BaseConnectableSurface::move_connection(QGraphicsSceneMouseEvent* mouse)
{
    if (connection_starter && mouse)
    {
        auto over = connector_at(mouse->scenePos());

        // Also executes if over == nullptr.
        if (connection_hover && connection_hover != over)
        {
            connection_hover->on_connection_hover_leave();
            connection_hover = nullptr;
        }

        // If previous if executed connection_hover is always nullptr.
        if (!connection_hover && over)
        {
            connection_hover = over;
            connection_hover->on_connection_hover_enter();
        }
    }
}

// Valid pointer if connecion was made, else: nullptr
BaseConnectable * BaseConnectableSurface::conclude_connection()
{
    if (connection_starter && connection_hover)
    {
        if (connection_starter->can_connect_with(connection_hover))
        {
            auto over = connection_hover;
            connection_starter = nullptr;
            connection_hover = nullptr;
            return over;
        }
    }
    return nullptr;
}
