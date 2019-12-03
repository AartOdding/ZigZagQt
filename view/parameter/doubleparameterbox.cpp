#include "doubleparameterbox.h"
#include "model/parameter/floatcomponent.h"
#include "utility/numeric.h"

#include <numeric>


DoubleParameterBox::DoubleParameterBox(QWidget * parent, FloatComponent* par)
    : QDoubleSpinBox(parent), parameter(par)
{
    Q_ASSERT(par);

    setMinimumWidth(50);
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setRange(par->get_min(), par->get_max());
    setValue(par->get_value());
    setSingleStep(0.1);

    connect(parameter, qOverload<double>(&BaseComponent::valueChanged), this, &DoubleParameterBox::on_parameter_value_changed);

    connect(parameter, &BaseComponent::flagsChanged, this, &DoubleParameterBox::on_parameter_flags_changed);
    connect(parameter, &BaseComponent::startedImportingFrom, this, &DoubleParameterBox::on_parameter_started_importing);
    connect(parameter, &BaseComponent::stoppedImportingFrom, this, &DoubleParameterBox::on_parameters_stopped_importing);
    connect(parameter, &FloatComponent::min_changed, this, &DoubleParameterBox::on_parameter_min_changed);
    connect(parameter, &FloatComponent::min_changed, this, &DoubleParameterBox::on_parameter_min_changed);

    if (!par->hasFlag(BaseComponent::MinimalUpdates))
    {
        connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), par, qOverload<double>(&BaseComponent::feed));
    }
    else
    {
        connect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
    }
    setEnabled(parameter->hasFlag(BaseComponent::IsEditable) && !parameter->isImporting());
}


void DoubleParameterBox::on_parameter_started_importing(BaseComponent *)
{
    setEnabled(false);
}


void DoubleParameterBox::on_parameters_stopped_importing(BaseComponent *)
{
    setEnabled(true);
}


void DoubleParameterBox::on_editing_finished()
{
    parameter->feed(value());
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


void DoubleParameterBox::on_parameter_flags_changed(int old_flags, int new_flags)
{
    if ((old_flags & BaseComponent::MinimalUpdates) != (new_flags & BaseComponent::MinimalUpdates))
    {
        if (!parameter->hasFlag(BaseComponent::MinimalUpdates))
        {
            disconnect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
            connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&BaseComponent::feed));
        }
        else
        {
            disconnect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&BaseComponent::feed));
            connect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
        }
    }
    setEnabled(parameter->hasFlag(BaseComponent::IsEditable) && !parameter->isImporting());
}
