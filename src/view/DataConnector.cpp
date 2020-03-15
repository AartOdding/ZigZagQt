#include "DataConnector.hpp"

#include "model/datainput.h"
#include "model/BaseDataType.hpp"

#include "view/OperatorNetworkView.hpp"
#include "view/operatorview.h"

#include "app.h"


#include <QPainter>
#include <QGraphicsSceneMouseEvent>




DataConnector::DataConnector(OperatorView& operatorView, DataInput& dataInput)
    : BaseConnector(/*application::project_view_model()*/nullptr, &operatorView), m_dataInput(&dataInput)
{
    m_color = m_dataInput->type()->gui_color;
}



DataConnector::DataConnector(OperatorView& operatorView, BaseDataType& dataOutput)
    : BaseConnector(/*application::project_view_model()*/nullptr, &operatorView), m_dataOutput(&dataOutput)
{
    m_color = m_dataOutput->getDescription()->gui_color;
}



void DataConnector::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    auto size = event->newSize();
    int pathHeight = std::min(size.height() - 4, 25.0);
    double x = isInput() ? 10 : -10;
    double y = 0.5 * (size.height() - pathHeight);
    m_path = QPainterPath(); // Clear it
    //path.addRoundedRect(QRectF(x, y, 20, path_height), 4, 4);
    m_path.addRoundedRect(QRectF(x, y, 25, pathHeight), pathHeight / 3.0, pathHeight / 3.0);
}



bool DataConnector::canConnectWith(BaseConnector* other) const
{
    auto o = dynamic_cast<DataConnector*>(other);

    if (o && o->isInput() != isInput())
    {
        return true;
    }
    return false;
}



void DataConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);

    auto brush = QBrush(m_hovered || isConnecting() ? m_color : QColor(55, 55, 55));
    auto pen = QPen(QBrush(m_color), 2);

    painter->fillPath(m_path, brush);
    painter->setPen(pen);
    painter->drawPath(m_path);
}



void DataConnector::connectionEvent(BaseConnector* other)
{
    auto o = dynamic_cast<DataConnector*>(other);

    if (o && isInput() != o->isInput())
    {
        if (isInput())
        {
            m_dataInput->connect_to(o->m_dataOutput);
        }
        else
        {
            m_dataOutput->connectTo(o->m_dataInput);
        }
    }
}



QColor DataConnector::getColor() const
{
    return m_color;
}



void DataConnector::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    auto connectionManager = getConnectionManager();

    if (connectionManager)
    {
        if (connectionManager->connectionStarted())
        {
            connectionManager->finishConnection(this);
            m_hovered = false;
            update();
        }
        else
        {
            connectionManager->startConnection(this);
        }
    }
}
