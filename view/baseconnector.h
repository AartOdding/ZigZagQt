#pragma once

#include <QGraphicsItem>



class ProjectSurface;


class BaseConnector
{
    friend class ProjectSurface;

public:


    virtual ~BaseConnector() = default;


    void start_connection();

    //void move_connection(QGraphicsSceneMouseEvent * mouse);
    //void move_connection(QGraphicsSceneHoverEvent * mouse);

    void conclude_connection();


    virtual bool can_connect_with(BaseConnector* other) const = 0;

    bool is_making_connection() const;

    ProjectSurface* get_connection_surface();


protected:

    virtual void on_connection_abort() { }

    virtual void on_connection_made(BaseConnector* other) = 0;

    virtual void on_connection_hover_enter(BaseConnector* originating_connection) { }

    virtual void on_connection_hover_leave(BaseConnector* originating_connection) { }


};
