#include "parameterpreview.h"
#include "model/baseoperator.h"

#include <QPainter>




ParameterPreview::ParameterPreview(BaseOperator* parent_operator)
    : BaseDataView(parent_operator, &Type)
{
    if (parent_operator->has_child_parameters())
    {
        auto par = parent_operator->get_child_parameters().at(0);

        if (par->num_components() != 0)
        {
            viewed_pararmeter_component = par->get_component(0);
            connect(parent_operator, &BaseOperator::update_view_requested, this, &ParameterPreview::onUpdateNecessary);

            if (dynamic_cast<Int64Component*>(viewed_pararmeter_component))
            {
                is_int = true;
                connect(viewed_pararmeter_component, qOverload<int64_t>(&BaseComponent::valueChanged),
                            this, &ParameterPreview::onValueChangedInt);
            }
            if (dynamic_cast<Float64Component*>(viewed_pararmeter_component))
            {
                is_int = false;
                connect(viewed_pararmeter_component, qOverload<double>(&BaseComponent::valueChanged),
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
