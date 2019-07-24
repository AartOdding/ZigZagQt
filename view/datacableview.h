#pragma once

#include <QObject>
#include <QGraphicsItem>


class ProgramView;
class DataConnectorView;


class DataCableView : public QObject,
                      public QGraphicsItem
{
    Q_OBJECT

public:

    static constexpr double tension = 0.6;
    static constexpr double flip_distance = 100;

    DataCableView(ProgramView * program_view, DataConnectorView * input_view, DataConnectorView * output_view);

    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool is_flipped() const;


public slots:

    void on_movement();


private:

    void build_path();


    ProgramView * program_view;
    DataConnectorView * input_view;
    DataConnectorView * output_view;

    QPainterPath path;
    QPainterPath path_in_scene;

};

