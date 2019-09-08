#pragma once

#include <QGraphicsWidget>


class OperatorView;
class ConnectionManager;


class BaseConnector : public QGraphicsWidget
{
public:

    BaseConnector(ConnectionManager* manager, OperatorView * operator_view);

    virtual ~BaseConnector() override = default;


    void try_connect();

    bool is_connecting() const;

    OperatorView * operator_view() const;


    virtual bool can_connect_with(BaseConnector* other) const = 0;

    virtual QColor get_color() const = 0;



    virtual bool connection_requested_event(BaseConnector* other) = 0;

    virtual void connection_aborted_event() { }


private:

    ConnectionManager* manager = nullptr;

    OperatorView * op_view = nullptr;


};
