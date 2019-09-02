#pragma once

#include "baseconnector.h"

class OperatorView;
class BaseParameter;



class ParameterConnector : public BaseConnector
{
public:

    ParameterConnector(OperatorView& op_view, bool is_input);


    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    bool can_connect_with(BaseConnector* other) const override;

    bool is_input() const { return is_input_; }


    OperatorView * const operator_view;

protected:

    void connection_requested_event(BaseConnector* other) override;
    void connection_aborted_event() override { update(); }

    void resizeEvent(QGraphicsSceneResizeEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override { hovered = true;  update(); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override { hovered = false; update(); }

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private slots:

    void item_selected(QAction *action);


private:

    QPainterPath path;

    bool is_input_;
    bool hovered = false;

};
