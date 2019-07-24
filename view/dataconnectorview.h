#pragma once

#include <QGraphicsItem>

class OperatorView;
class DataBlockInput;
class BaseDataBlock;


class DataConnectorView : public QGraphicsItem
{

public:

    DataConnectorView(OperatorView& parent, DataBlockInput& input, int height);

    DataConnectorView(OperatorView& parent, BaseDataBlock& output, int height);


    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool is_input() const { return data_input && !data_output; }

    bool is_output() const { return data_output && !data_input; }

    OperatorView * const parent_view;

protected:

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent * event) override;


private:

    DataBlockInput* data_input = nullptr;
    BaseDataBlock* data_output = nullptr;

    QRectF bounds;
    QRectF clip_bounds;

    bool highlighted = false;
    bool is_dragging = false;

    QPainterPath path;

};
