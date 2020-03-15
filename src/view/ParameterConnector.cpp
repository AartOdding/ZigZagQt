#include "ParameterConnector.hpp"
#include "app.h"
#include "operatorview.h"
#include "model/parameter/BaseParameter.hpp"
#include "model/BaseOperator.hpp"
#include "model/datainput.h"
#include "model/BaseDataType.hpp"
#include "view/OperatorNetworkView.hpp"
#include "view/PopupWindow.hpp"
#include "view/connection/ConnectionEditor.hpp"

#include <QApplication>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneResizeEvent>

#include <iostream>


ParameterConnector::ParameterConnector(OperatorView& operatorView, bool isInput)
    : BaseConnector(/*application::project_view_model()*/nullptr, &operatorView), m_isInput(isInput)
{
}


void ParameterConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);

    auto brush = QBrush(m_hovered || isConnecting() ? QColor(255, 255, 255) : QColor(55, 55, 55));
    auto pen = QPen(QBrush(QColor(255, 255, 255)), 2);

    painter->fillPath(m_path, brush);
    painter->setPen(pen);
    painter->drawPath(m_path);
}


bool ParameterConnector::canConnectWith(BaseConnector* other) const
{
    auto o = dynamic_cast<ParameterConnector*>(other);

    if (o && o->isInput() != isInput())
    {
        return true;
    }
    return false;
}


void ParameterConnector::connectionEvent(BaseConnector* other)
{
    auto o = dynamic_cast<ParameterConnector*>(other);

    if (o && isInput() != o->isInput())
    {
        auto active = QApplication::activeWindow();

        if (active)
        {
            auto con = new ConnectionEditor(getOperatorModel(), other->getOperatorModel(), nullptr);
            auto popup = new PopupWindow(con);
            popup->resize(900, 400);
            popup->move(active->geometry().center() - QPoint(450, 200));
            //popup->setModal(true);
            popup->show();
        }
    }
}


void ParameterConnector::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    auto size = event->newSize();
    int path_height = std::min(size.height() - 4, 18.0);
    double x = isInput() ? 13 : -8;
    double y = 0.5 * (size.height() - path_height);
    m_path = QPainterPath(); // Clear it
    m_path.addRoundedRect(QRectF(x, y, 20, path_height), path_height / 3.0, path_height / 3.0);
}


void ParameterConnector::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
