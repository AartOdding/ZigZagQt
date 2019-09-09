#pragma once

#include <QObject>
#include <QGraphicsItem>


class ProjectScopeView;
class DataConnector;
class BaseConnector;


class Cable : public QObject,
              public QGraphicsItem
{
    Q_OBJECT

public:

    static constexpr double tension = 0.6;
    static constexpr double flip_distance = 100;

    Cable(ProjectScopeView * program_view, BaseConnector * output, BaseConnector * input);

    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool is_flipped() const;

    virtual bool contains(const QPointF &point) const override;


public slots:

    void on_movement();


private:

    void build_path();


    ProjectScopeView * program_view;
    BaseConnector * output_connector;
    BaseConnector * input_connector;

    QColor color;
    QPainterPath path;
    QPainterPath path_in_scene;

};

