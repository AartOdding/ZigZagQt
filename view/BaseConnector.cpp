#include "BaseConnector.hpp"
#include "ConnectionManager.hpp"
#include "view/operatorview.h"



BaseConnector::BaseConnector(ConnectionManager* manager, OperatorView * operatorView)
    : m_connectionManager(manager),
      m_operatorView(operatorView)
{
    setFlag(QGraphicsItem::ItemClipsToShape); // Enable clipping.
    setFlag(QGraphicsItem::ItemIsFocusable); // Because we need focus out event.
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setMinimumSize(10, 10);
    setPreferredSize(10, 10);
}



OperatorView * BaseConnector::getOperatorView() const
{
    return m_operatorView;
}



BaseOperator * BaseConnector::getOperatorModel() const
{
    if (m_operatorView)
    {
        return &m_operatorView->operator_model;
    }
    return nullptr;
}



ConnectionManager * BaseConnector::getConnectionManager() const
{
    return m_connectionManager;
}



bool BaseConnector::isConnecting() const
{
    return m_connectionManager->getStartingConnector() == this;
}
