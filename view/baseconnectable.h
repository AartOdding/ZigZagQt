#pragma once

#include <QGraphicsItem>



class BaseConnectableSurface;


class BaseConnectable
{
    friend class BaseConnectableSurface;

public:


    BaseConnectable(BaseConnectableSurface* surface);

    virtual ~BaseConnectable() = default;


    void start_connection();

    void move_connection(QGraphicsSceneMouseEvent * mouse);

    BaseConnectable * conclude_connection();


    virtual bool can_connect_with(BaseConnectable* other) const = 0;


protected:

    // Only called for the BaseConnecable that started the connection!
    virtual void on_connection_made(BaseConnectable* originating_connection);

    virtual void on_connection_hover_enter();

    virtual void on_connection_hover_leave();

private:

    BaseConnectableSurface * surface;


};
