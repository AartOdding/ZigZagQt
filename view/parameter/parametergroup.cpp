#include "parametergroup.h"

#include "model/parameter/baseparameter.h"
#include "model/parameter/buttonparameter.h"
#include "model/parameter/parameterowner.h"
#include "model/parameter/parameterrow.h"

#include "enumwidget.h"

#include "model/parameter/intparametercomponent.h"
#include "model/parameter/floatparametercomponent.h"
#include "int64parameterbox.h"
#include "doubleparameterbox.h"
#include "buttonparameterbox.h"

#include <QLabel>



ParameterGroup::ParameterGroup(QWidget *parent, ParameterOwner* parameters)
    : QFrame(parent), parameter_owner(parameters)
{
    Q_ASSERT(parent);
    Q_ASSERT(parameters);

    if (parameters->is_operator())
    {
        setFrameStyle(QFrame::NoFrame);
        layout.setMargin(0);
    }
    else
    {
        setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        layout.addRow(new QLabel(parameter_owner->get_name()));
        layout.setMargin(10);
    }


    for (auto parameter : parameter_owner->get_parameters())
    {
        if (parameter->get_parameter_type() == ParameterType::ParameterOwner)
        {
            auto owner = static_cast<ParameterOwner*>(parameter);

            if (!owner->get_parameters().empty())
            {
                layout.addRow(new ParameterGroup(this, owner));
            }
        }
        else
        {
            layout.addRow(parameter->get_name(), new_widget_for_parameter(parameter));
        }
    }
}


QWidget* ParameterGroup::new_widget_for_parameter(BaseParameter* par)
{
    Q_ASSERT(par);

    if (par->get_parameter_type() == ParameterType::Enum)
    {
        return new EnumWidget(this, static_cast<EnumPar*>(par));
    }
    else if (par->get_parameter_type() == ParameterType::Button)
    {
        return new ButtonParameterBox(this, static_cast<ButtonPar*>(par));
    }
    else if (par->get_component(0)->get_component_type() == BaseParameterComponent::Int64)
    {
        if (par->num_components() == 1)
        {
            return new Int64ParameterBox(this, static_cast<IntParameterComponent*>(par->get_component(0)));
        }
        else
        {
            auto widget = new QWidget(this);
            auto widget_layout = new QHBoxLayout(widget);
            widget_layout->setMargin(0);

            for (int i = 0; i < par->num_components(); ++i)
            {
                widget_layout->addWidget(new Int64ParameterBox(this, static_cast<IntParameterComponent*>(par->get_component(i))));
            }
            return widget;
        }
    }
    else if (par->get_component(0)->get_component_type() == BaseParameterComponent::Float64)
    {
        if (par->num_components() == 1)
        {
            return new DoubleParameterBox(this, static_cast<FloatParameterComponent*>(par->get_component(0)));
        }
        else
        {
            auto widget = new QWidget(this);
            auto widget_layout = new QHBoxLayout(widget);
            widget_layout->setMargin(0);

            for (int i = 0; i < par->num_components(); ++i)
            {
                widget_layout->addWidget(new DoubleParameterBox(this, static_cast<FloatParameterComponent*>(par->get_component(i))));
            }
            return widget;
        }
    }
    return nullptr;
}
