#include "basedataview.h"
#include "view/operatorview.h"

#include <QWidget>
#include <QPainter>


BaseDataView::BaseDataView()
{
    //setFlag(QGraphicsItem::ItemIgnoresTransformations);
}


QRectF BaseDataView::boundingRect() const
{
    return bounds;
}


void BaseDataView::set_bounds(double x, double y, double w, double h)
{
    bounds = QRectF(x, y, w, h);
    prepareGeometryChange();
}

