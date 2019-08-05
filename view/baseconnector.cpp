#include "application.h"
#include "baseconnector.h"
#include "projectsurface.h"

#include <QGraphicsSceneMouseEvent>



void BaseConnector::start_connection()
{
    application::project_view_model()->start_connecting(this);
}

/*
void BaseConnector::move_connection(QGraphicsSceneMouseEvent * mouse)
{
    application::project_view_model()->move_connection(mouse);
}


void BaseConnector::move_connection(QGraphicsSceneHoverEvent * mouse)
{
    application::project_view_model()->move_connection(mouse);
}
*/

void BaseConnector::conclude_connection()
{
    application::project_view_model()->stop_connecting();
}


bool BaseConnector::is_making_connection() const
{
    return application::project_view_model()->connection_starter == this;
}


ProjectSurface* BaseConnector::get_connection_surface()
{
    return application::project_view_model();
}
