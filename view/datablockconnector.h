#pragma once

#include <QGraphicsItem>

#include "baseconnector.h"

class OperatorView;
class DataBlockInput;
class BaseDataBlock;


class DataBlockConnector : public BaseConnector
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

    void highlight_on_event() override;
    void highlight_off_event() override;

    void connection_made_event(BaseConnector* other) override;


private:

    DataBlockInput* data_input = nullptr;
    BaseDataBlock* data_output = nullptr;

    QRectF bounds;
    QRectF clip_bounds;

    QPainterPath path;

    bool highlighted = false;

};
