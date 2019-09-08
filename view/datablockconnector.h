#pragma once

#include "baseconnector.h"

class OperatorView;
class DataInput;
class BaseDataType;




class DataBlockConnector : public BaseConnector
{

public:

    DataBlockConnector(OperatorView& op_view, DataInput& input);

    DataBlockConnector(OperatorView& op_view, BaseDataType& output);


    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool is_input() const { return data_input && !data_output; }

    bool is_output() const { return data_output && !data_input; }

    bool can_connect_with(BaseConnector* other) const override;


    QColor get_color() const override;


protected:

    bool connection_requested_event(BaseConnector* other) override;
    void connection_aborted_event() override { update(); }

    void resizeEvent(QGraphicsSceneResizeEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override { hovered = true;  update(); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override { hovered = false; update(); }

    void mousePressEvent(QGraphicsSceneMouseEvent *) override { try_connect(); }


private:

    DataInput* data_input = nullptr;
    BaseDataType* data_output = nullptr;

    QColor color;
    QPainterPath path;

    bool hovered = false;

};
