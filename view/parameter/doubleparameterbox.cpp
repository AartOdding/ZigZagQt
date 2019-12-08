#include "doubleparameterbox.h"
#include "model/parameter/Float64Component.hpp"
#include "utility/numeric.h"

#include <numeric>


DoubleParameterBox::DoubleParameterBox(QWidget * parent, Float64Component* par)
    : QDoubleSpinBox(parent), parameter(par)
{
    Q_ASSERT(par);

    setMinimumWidth(50);
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setRange(par->getMin(), par->getMax());
    setValue(par->getValue());
    setSingleStep(0.1);

    connect(parameter, qOverload<double>(&BaseComponent::valueChanged), this, &DoubleParameterBox::on_parameter_value_changed);

    connect(parameter, &BaseComponent::flagChanged, this, &DoubleParameterBox::onFlagsChanged);
    connect(parameter, &BaseComponent::startedImportingFrom, this, &DoubleParameterBox::on_parameter_started_importing);
    connect(parameter, &BaseComponent::stoppedImportingFrom, this, &DoubleParameterBox::on_parameters_stopped_importing);
    connect(parameter, &Float64Component::minChanged, this, &DoubleParameterBox::on_parameter_min_changed);
    connect(parameter, &Float64Component::minChanged, this, &DoubleParameterBox::on_parameter_min_changed);

    if (!par->hasFlag(ParameterFlags::MinimalUpdates))
    {
        connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), par, qOverload<double>(&BaseComponent::change));
    }
    else
    {
        connect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
    }
    setEnabled(parameter->hasFlag(ParameterFlags::IsEditable) && !parameter->isImporting());
}


void DoubleParameterBox::on_parameter_started_importing(BaseComponent *)
{
    setEnabled(false);
}


void DoubleParameterBox::on_parameters_stopped_importing(BaseComponent *)
{
    setEnabled(parameter->hasFlag(ParameterFlags::IsEditable));
}


void DoubleParameterBox::on_editing_finished()
{
    parameter->change(value());
}


void DoubleParameterBox::on_parameter_value_changed(double new_value)
{
    setValue(new_value);
}


void DoubleParameterBox::on_parameter_min_changed(double new_min)
{
    setMinimum(new_min);
}


void DoubleParameterBox::on_parameter_max_changed(double new_max)
{
    setMaximum(new_max);
}


void DoubleParameterBox::onFlagsChanged(ParameterFlags flag, bool value)
{
    if (flag == ParameterFlags::IsEditable)
    {
        setEnabled(value && !parameter->isImporting());
    }
    else if (flag == ParameterFlags::MinimalUpdates)
    {
        if (value)
        {
            disconnect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
            connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&BaseComponent::change));
        }
        else
        {
            disconnect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&BaseComponent::change));
            connect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
        }
    }
}

/*
void DoubleParameterBox::on_parameter_flags_changed(int old_flags, int new_flags)
{
    if ((old_flags & BaseComponent::MinimalUpdates) != (new_flags & BaseComponent::MinimalUpdates))
    {
        if (!parameter->hasFlag(BaseComponent::MinimalUpdates))
        {
            disconnect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
            connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&BaseComponent::change));
        }
        else
        {
            disconnect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&BaseComponent::change));
            connect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
        }
    }
    setEnabled(parameter->hasFlag(BaseComponent::IsEditable) && !parameter->isImporting());
}*/
