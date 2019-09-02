#include "connectionmanager.h"
#include "baseconnector.h"

#include "operatorview.h"



void ConnectionManager::try_connect(BaseConnector* connector)
{
    if (m_active_connector != connector)
    {
        if (connector && m_active_connector) // If now have two connectors
        {
            if (m_active_connector->can_connect_with(connector))
            {
                m_active_connector->connection_requested_event(connector);
                m_active_connector = nullptr;
                return;
            }
        }
        // Can only reach here if no connection was possible
        if (m_active_connector)
        {
            cancel_connection();
        }
        // Start new connection
        m_active_connector = connector;
    }
}


void ConnectionManager::cancel_connection()
{
    if (m_active_connector)
    {
        auto old = m_active_connector;
        m_active_connector = nullptr;
        old->connection_aborted_event();
    }
}


bool ConnectionManager::is_connecting() const
{
    return m_active_connector != nullptr;
}


BaseConnector * ConnectionManager::active_connector() const
{
    return m_active_connector;
}


/*
void ProjectSurface::mouse_movement(const QPointF &scene_pos)
{
    if (m_active_connector)
    {
        auto over = dynamic_cast<BaseConnector *>(itemAt(scene_pos, QTransform()));

        // Also executes if over == nullptr.
        if (connection_hover && connection_hover != over)
        {
            connection_hover->set_highlighted(false);
            connection_hover = nullptr;
        }

        // If previous if executed connection_hover is always nullptr.
        if (!connection_hover && over && m_active_connector != over)
        {
            connection_hover = over;

            if (over->can_connect_with(m_active_connector)
                && m_active_connector->can_connect_with(over))
            {
                connection_hover->set_highlighted(true);
            }
        }
    }
}*/


/*
    if (m_active_connector && connection_hover
            && m_active_connector->can_connect_with(connection_hover)
            && connection_hover->can_connect_with(m_active_connector))
    {
        m_active_connector->set_highlighted(false);
        connection_hover->set_highlighted(false);
        m_active_connector->connection_made_event(connection_hover);
        connection_hover->connection_made_event(m_active_connector);
    }
    else if (m_active_connector)
    {
        m_active_connector->set_highlighted(false);
        m_active_connector->connection_aborted_event();
    }
    m_active_connector = nullptr;
    connection_hover = nullptr;
 */


/*
bool ProjectSurface::is_hovering_connector() const
{
    return connection_hover != nullptr;
}*/
