#pragma once

#include <QGraphicsItem>

#include "baseconnector.h"

class OperatorView;
class DataBlockInput;
class BaseDataBlock;


class DataBlockConnector : public QGraphicsItem,
                           public BaseConnector
{

public:

    DataBlockConnector(OperatorView& parent, DataBlockInput& input, int height);

    DataBlockConnector(OperatorView& parent, BaseDataBlock& output, int height);


    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool is_input() const { return data_input && !data_output; }

    bool is_output() const { return data_output && !data_input; }

    bool can_connect_with(BaseConnector* other) const override;

    OperatorView * const parent_view;


protected:

    void focusInEvent(QFocusEvent *event) override { }
    void focusOutEvent(QFocusEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void on_connection_hover_enter(BaseConnector* originating_connection) override;
    void on_connection_hover_leave(BaseConnector* originating_connection) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override { }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void on_connection_abort() override;
    void on_connection_made(BaseConnector* other) override;


private:

    DataBlockInput* data_input = nullptr;
    BaseDataBlock* data_output = nullptr;

    QRectF bounds;
    QRectF clip_bounds;

    bool highlighted = false;

    QPainterPath path;

};
