#pragma once

#include "BaseConnector.hpp"

class OperatorView;
class BaseParameter;



class ParameterConnector : public BaseConnector
{
    Q_OBJECT

public:

    ParameterConnector(OperatorView& operatorView, bool isInput);

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;


    bool isInput() const { return m_isInput; }


    void connectionEvent(BaseConnector* other) override;
    void connectionCancelEvent() override { update(); }

    bool canConnectWith(BaseConnector* other) const override;

protected:

    void resizeEvent(QGraphicsSceneResizeEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override { m_hovered = true;  update(); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override { m_hovered = false; update(); }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


private:

    QPainterPath m_path;

    bool m_isInput;
    bool m_hovered = false;

};
