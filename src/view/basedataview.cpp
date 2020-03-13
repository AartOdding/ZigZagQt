#include "basedataview.h"
#include "view/operatorview.h"
#include "model/BaseOperator.hpp"

#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>


BaseDataView::BaseDataView(BaseOperator * parent_operator, const DataViewDescription *type)
    : BaseZigZagObject(parent_operator, type->name.c_str()),
      type_info(type)
{
    //setFlag(QGraphicsItem::ItemIgnoresTransformations);
}


BaseDataView::~BaseDataView()
{
    setParentItem(nullptr);
    scene()->removeItem(this);
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

