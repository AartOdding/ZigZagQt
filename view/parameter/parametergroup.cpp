#include "parametergroup.h"

#include "model/baseoperator.h"
#include "model/parameter/BaseParameter.hpp"
#include "model/parameter/buttonparameter.h"
#include "model/parameter/parameterrow.h"

#include "enumwidget.h"

#include "model/parameter/Int64Component.hpp"
#include "model/parameter/Float64Component.hpp"
#include "int64parameterbox.h"
#include "doubleparameterbox.h"
#include "buttonparameterbox.h"

#include <QLabel>



ParameterGroup::ParameterGroup(QWidget *parent, BaseZigZagObject* parameters_)
    : QFrame(parent), parameters(parameters_)
{
    Q_ASSERT(parent);
    Q_ASSERT(parameters);

    if (dynamic_cast<BaseOperator*>(parameters))
    {
        setFrameStyle(QFrame::NoFrame);
        layout.setMargin(0);
    }
    else
    {
        setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        layout.addRow(new QLabel(parameters->getName()));
        layout.setMargin(10);
    }
    layout.setVerticalSpacing(4);
    layout.setHorizontalSpacing(7);

    for (auto par : parameters->getParameters())
    {
        layout.addRow(par->getName(), new_widget_for_parameter(par));
    }

    for (auto child : parameters->getChildren())
    {
        layout.addRow(new ParameterGroup(this, child));
    }
}


QWidget* ParameterGroup::new_widget_for_parameter(BaseParameter* par)
{
    Q_ASSERT(par);

    if (par->getParameterType() == ParameterType::Enum)
    {
        return new EnumWidget(this, static_cast<EnumPar*>(par));
    }
    else if (par->getParameterType() == ParameterType::Button)
    {
        return new ButtonParameterBox(this, static_cast<ButtonPar*>(par));
    }
    else if (par->getParameterType() == ParameterType::Int  ||
             par->getParameterType() == ParameterType::Int2 ||
             par->getParameterType() == ParameterType::Int3 ||
             par->getParameterType() == ParameterType::Int4)
    {
        if (par->getComponents().size() == 1)
        {
            return new Int64ParameterBox(this, static_cast<Int64Component*>(par->getComponents()[0]));
        }
        else
        {
            auto widget = new QWidget(this);
            auto widget_layout = new QHBoxLayout(widget);
            widget_layout->setMargin(0);
            widget_layout->setSpacing(0);

            for (int i = 0; i < par->getComponents().size(); ++i)
            {
                widget_layout->addWidget(new Int64ParameterBox(this, static_cast<Int64Component*>(par->getComponents()[i])));
            }
            return widget;
        }
    }
    else if (par->getParameterType() == ParameterType::Float  ||
             par->getParameterType() == ParameterType::Float2 ||
             par->getParameterType() == ParameterType::Float3 ||
             par->getParameterType() == ParameterType::Float4)
    {
        if (par->getComponents().size() == 1)
        {
            return new DoubleParameterBox(this, static_cast<Float64Component*>(par->getComponents()[0]));
        }
        else
        {
            auto widget = new QWidget(this);
            auto widget_layout = new QHBoxLayout(widget);
            widget_layout->setMargin(0);
            widget_layout->setSpacing(0);

            for (int i = 0; i < par->getComponents().size(); ++i)
            {
                widget_layout->addWidget(new DoubleParameterBox(this, static_cast<Float64Component*>(par->getComponents()[i])));
            }
            return widget;
        }
    }
    return nullptr;
}
