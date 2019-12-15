#include "parameterpreview.h"
#include "model/baseoperator.h"

#include <QPainter>




ParameterPreview::ParameterPreview(BaseOperator* parent_operator)
    : BaseDataView(parent_operator, &Type)
{
    if (parent_operator->getParameters().size() > 0)
    {
        auto par = parent_operator->getParameters()[0];

        if (par->getComponents().size() > 0)
        {
            viewedComponent = par->getComponents()[0];
            QObject::connect(parent_operator, &BaseOperator::update_view_requested, this, &ParameterPreview::onUpdateNecessary);

            if (qobject_cast<Int64Component*>(viewedComponent))
            {
                is_int = true;
                QObject::connect(viewedComponent, qOverload<int64_t>(&BaseComponent::valueChanged),
                            this, &ParameterPreview::onValueChangedInt);
            }
            if (qobject_cast<Float64Component*>(viewedComponent))
            {
                is_int = false;
                QObject::connect(viewedComponent, qOverload<double>(&BaseComponent::valueChanged),
                            this, &ParameterPreview::onValueChangedDouble);
            }
        }
    }
}


void ParameterPreview::onUpdateNecessary()
{
    update();
}


void ParameterPreview::onValueChangedDouble(double newValue)
{
    floatValue = newValue;
}


void ParameterPreview::onValueChangedInt(int64_t newValue)
{
    intValue = newValue;
}


void ParameterPreview::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto font = painter->font();
    font.setPixelSize(46);
    painter->setFont(font);
    painter->setPen(Qt::white);

    if (is_int)
    {
        painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(intValue));
    }
    else
    {
        painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(floatValue, 'f', 2));
    }
}
