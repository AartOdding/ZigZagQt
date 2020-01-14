#pragma once

#include "view/BaseConnector.hpp"

class OperatorView;
class DataInput;
class BaseDataType;




class DataConnector : public BaseConnector
{

public:

    DataConnector(OperatorView& operatorView, DataInput& input);

    DataConnector(OperatorView& operatorView, BaseDataType& output);


    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool isInput() const { return m_dataInput && !m_dataOutput; }

    bool isOutput() const { return m_dataOutput && !m_dataInput; }


    QColor getColor() const;


    void connectionEvent(BaseConnector* other) override;
    void connectionCancelEvent() override { update(); }

    bool canConnectWith(BaseConnector* other) const override;

protected:

    void resizeEvent(QGraphicsSceneResizeEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override { m_hovered = true;  update(); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override { m_hovered = false; update(); }

    void mousePressEvent(QGraphicsSceneMouseEvent *) override;


private:

    DataInput* m_dataInput = nullptr;
    BaseDataType* m_dataOutput = nullptr;

    QColor m_color;
    QPainterPath m_path;

    bool m_hovered = false;

};
