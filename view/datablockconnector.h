#pragma once

#include <QGraphicsItem>

#include "baseconnector.h"

class OperatorView;
class DataInput;
class BaseDataType;


class DataBlockConnector : public BaseConnector
{

public:

    DataBlockConnector(OperatorView& parent, DataInput& input, int height);

    DataBlockConnector(OperatorView& parent, BaseDataType& output, int height);


    QRectF boundingRect() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool is_input() const { return data_input && !data_output; }

    bool is_output() const { return data_output && !data_input; }

    bool can_connect_with(BaseConnector* other) const override;

    OperatorView * const parent_view;

    QColor get_color() const;


protected:

    void highlight_on_event() override;
    void highlight_off_event() override;

    void connection_made_event(BaseConnector* other) override;


private:

    DataInput* data_input = nullptr;
    BaseDataType* data_output = nullptr;

    QRectF bounds;
    QRectF clip_bounds;
    QColor color;

    QPainterPath path;

    bool highlighted = false;

};
