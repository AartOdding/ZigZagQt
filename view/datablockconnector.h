#pragma once

#include <QGraphicsItem>

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


    OperatorView * const operator_view;

    QColor get_color() const;


protected:

    void connection_made_event(BaseConnector* other) override;

    void resizeEvent(QGraphicsSceneResizeEvent *event) override;


private:

    DataInput* data_input = nullptr;
    BaseDataType* data_output = nullptr;

    QColor color;
    QPainterPath path;

};
