#include "basedataview.h"
#include "view/operatorview.h"
#include "model/baseoperator.h"

#include <QWidget>
#include <QPainter>


BaseDataView::BaseDataView(BaseOperator * parent_operator, const DataViewTypeInfo *type)
    : BaseParameter(parent_operator, ParameterType::DataView, type->name.c_str()), type_info(type)
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

