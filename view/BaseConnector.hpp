#pragma once

#include <QGraphicsWidget>


class BaseOperator;
class OperatorView;
class ConnectionManager;


class BaseConnector : public QGraphicsWidget
{

public:

    BaseConnector(ConnectionManager* connectionManager, OperatorView * operatorView);

    virtual ~BaseConnector() override = default;


    OperatorView * getOperatorView() const;
    BaseOperator * getOperatorModel() const;
    ConnectionManager * getConnectionManager() const;

    bool isConnecting() const;

    /*
     * These two functions are called for the first connector that initiates a connection.
     * because there is a time difference between when the first connection says it is
     * wanting to be connected, and when a second connector has been selected to make the
     * connection with. This means the first connector needs to be informed about what
     * has happened.
     */
    virtual void connectionEvent(BaseConnector* other) = 0;
    virtual void connectionCancelEvent() { }

    /*
     * should be implemented to inform the connectionManager that it can or cannot make a
     * connection with another connector.
     */
    virtual bool canConnectWith(BaseConnector* other) const = 0;

private:

    ConnectionManager * m_connectionManager = nullptr;

    OperatorView * m_operatorView = nullptr;


};
