#include "view/connectorview.h"
#include "view/operatorview.h"

#include <QPainter>



ConnectorView::ConnectorView(OperatorView& parent, BaseOperator* op_model, int i, bool input)
    : QGraphicsItem(&parent), operator_model(op_model), index(i), is_input(input)
{ }


QRectF ConnectorView::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}


void ConnectorView::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    auto brush = QBrush(QColor(205, 255, 0));
    painter->setBrush(brush);
    painter->drawEllipse(-5, -5, 10, 10);
    //painter->fillRect(0, 0, 60, 40, brush);
}
