#pragma once

#include <QVector>
#include <QObject>
#include <QPointer>
#include <QGraphicsItem>

#include "connectorview.h"


class BaseTOP;
class ProgramModel;



class OperatorView : public QObject,
                     public QGraphicsItem
{
    Q_OBJECT

public:

    OperatorView(ProgramModel& m, BaseTOP* pointer, qint64 id);

    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;


public slots:

    void on_operator_moved(int to_x, int to_y);

    void on_num_inputs_changed(int new_num_inputs);


protected:

    void mousePressEvent(QGraphicsSceneMouseEvent * event) override { }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:

    static constexpr int width = 120;
    static constexpr int height = 80;

    bool was_dragged = false;

    ProgramModel& model;
    QPointer<BaseTOP> operator_pointer;
    qint64 operator_id;

    int position_x, position_y;

    QVector<ConnectorView*> input_connectors;
    ConnectorView output_connector;


};
