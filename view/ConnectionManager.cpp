#include "ConnectionManager.hpp"
#include "BaseConnector.hpp"

#include "operatorview.h"



void ConnectionManager::startConnection(BaseConnector* connector)
{
    if (m_startingConnector != connector)
    {
        if (connector && m_startingConnector) // If now have two connectors
        {
            if (m_startingConnector->canConnectWith(connector))
            {
                m_startingConnector->connectionEvent(connector);
                m_startingConnector = nullptr;
                return;
            }
        }
        // Can only reach here if no connection was possible
        if (m_startingConnector)
        {
            cancelConnection();
        }
        // Start new connection
        m_startingConnector = connector;
    }
}


std::pair<bool, BaseConnector*> ConnectionManager::finishConnection(BaseConnector* connector)
{
    std::pair<bool, BaseConnector*> returnValue{ false, nullptr };

    if (m_startingConnector && connector && m_startingConnector != connector)
    {
        if (m_startingConnector->canConnectWith(connector))
        {
            returnValue = { true, m_startingConnector };
            m_startingConnector->connectionEvent(connector);
        }
    }

    if (m_startingConnector && !returnValue.first)
    {
        m_startingConnector->connectionCancelEvent();
    }

    m_startingConnector = nullptr;
    return returnValue;
}


void ConnectionManager::cancelConnection()
{
    if (m_startingConnector)
    {
        auto old = m_startingConnector;
        m_startingConnector = nullptr;
        old->connectionCancelEvent();
    }
}


bool ConnectionManager::connectionStarted() const
{
    return m_startingConnector != nullptr;
}


BaseConnector * ConnectionManager::getStartingConnector() const
{
    return m_startingConnector;
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
