#pragma once


#include <QGraphicsScene>

class BaseConnector;



class ProjectSurface : public QGraphicsScene
{
    Q_OBJECT

public:

    ProjectSurface();

    virtual ~ProjectSurface() = default;

    void start_connecting(BaseConnector* connector);

    void stop_connecting();

    void mouse_movement(const QPointF& scene_pos);


    bool is_making_connection() const;

    bool is_hovering_connector() const;

private:

    friend class BaseConnector;

    BaseConnector * connection_starter = nullptr;
    BaseConnector * connection_hover = nullptr;



};
