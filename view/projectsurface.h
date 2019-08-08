#pragma once


#include <QGraphicsScene>

class BaseOperator;
class BaseConnector;
class OperatorView;



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


public slots:

    void set_focus_operator(OperatorView* op);


signals:

    void focus_operator_changed(BaseOperator* op);


private:

    friend class BaseConnector;

    BaseConnector * connection_starter = nullptr;
    BaseConnector * connection_hover = nullptr;

    OperatorView * focus_operator = nullptr;

};
