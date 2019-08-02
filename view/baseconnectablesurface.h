#pragma once

#include <QGraphicsScene>

class BaseConnectable;


class BaseConnectableSurface
{
    friend class BaseConnectable;


public:

    virtual ~BaseConnectableSurface() = default;

    void start_connection(BaseConnectable* connector);

    void move_connection(QGraphicsSceneMouseEvent* mouse);

    // Valid pointer if connecion was made, else: nullptr
    BaseConnectable * conclude_connection();

    virtual BaseConnectable * connector_at(const QPointF& pos) const = 0;

private:

    BaseConnectable * connection_starter;
    BaseConnectable * connection_hover;


};
