#include "parameterview.h"
#include "model/BaseOperator.hpp"

#include <QPainter>




ParameterView::ParameterView(BaseOperator* parent_operator, const BaseComponent* component)
    : BaseDataView(parent_operator, &Type),
      m_viewedComponent(component)
{
    auto parameters = parent_operator->findChildren<BaseParameter*>(QString(), Qt::FindDirectChildrenOnly);

    if (parameters.size() > 0)
    {
        auto par = parameters[0];

        if (par->getComponents().size() > 0)
        {
            m_viewedComponent = par->getComponents()[0];
            QObject::connect(parent_operator, &BaseOperator::update_view_requested, this, &ParameterView::onUpdateNecessary);

            if (qobject_cast<const Int64Component*>(m_viewedComponent))
            {
                is_int = true;
                QObject::connect(m_viewedComponent, qOverload<int64_t>(&BaseComponent::valueChanged),
                            this, &ParameterView::onValueChangedInt);
            }
            if (qobject_cast<const Float64Component*>(m_viewedComponent))
            {
                is_int = false;
                QObject::connect(m_viewedComponent, qOverload<double>(&BaseComponent::valueChanged),
                            this, &ParameterView::onValueChangedDouble);
            }
        }
    }
}


void ParameterView::onUpdateNecessary()
{
    update();
}


void ParameterView::onValueChangedDouble(double newValue)
{
    floatValue = newValue;
}


void ParameterView::onValueChangedInt(int64_t newValue)
{
    intValue = newValue;
}


void ParameterView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
