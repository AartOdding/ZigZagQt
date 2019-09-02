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

    bool is_input() const { return m_is_input; }


    OperatorView * const operator_view;

protected:

    void connection_made_event(BaseConnector* other) override;

    void resizeEvent(QGraphicsSceneResizeEvent *event) override;


private:

    QPainterPath path;

    bool highlighted = false;
    bool m_is_input;

};
