#pragma once

#include <QObject>
#include <QGraphicsItem>


class ProjectScopeView;
class DataBlockConnector;
class BaseConnector;


class DataBlockCable : public QObject,
                       public QGraphicsItem
{
    Q_OBJECT

public:

    static constexpr double tension = 0.6;
    static constexpr double flip_distance = 100;

    DataBlockCable(ProjectScopeView * program_view, BaseConnector * input_view, BaseConnector * output_view);

    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool is_flipped() const;

    virtual bool contains(const QPointF &point) const override;


public slots:

    void on_movement();


private:

    void build_path();


    ProjectScopeView * program_view;
    BaseConnector * input_view;
    BaseConnector * output_view;

    QColor color;
    QPainterPath path;
    QPainterPath path_in_scene;

};

