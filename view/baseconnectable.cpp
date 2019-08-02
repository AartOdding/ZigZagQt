#include "baseconnectable.h"
#include "baseconnectablesurface.h"

#include <QGraphicsSceneMouseEvent>


BaseConnectable::BaseConnectable(BaseConnectableSurface* s)
    : surface(s)
{

}


void BaseConnectable::start_connection()
{
    surface->start_connection(this);
}


void BaseConnectable::move_connection(QGraphicsSceneMouseEvent * mouse)
{
    surface->move_connection(mouse);
}


BaseConnectable * BaseConnectable::conclude_connection()
{
    return surface->conclude_connection();
}
