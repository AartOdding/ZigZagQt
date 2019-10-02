#include "doubleparameterbox.h"
#include "model/parameter/floatparametercomponent.h"
#include "utility/numeric.h"

#include <numeric>


DoubleParameterBox::DoubleParameterBox(QWidget * parent, FloatParameterComponent* par)
    : QDoubleSpinBox(parent), parameter(par)
{
    Q_ASSERT(par);

    setMinimumWidth(50);
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setRange(par->get_min(), par->get_max());
    setValue(par->get());
    setSingleStep(0.1);

    connect(parameter, qOverload<double>(&BaseParameterComponent::value_changed), this, &DoubleParameterBox::on_parameter_value_changed);

    connect(parameter, &BaseParameterComponent::flags_changed, this, &DoubleParameterBox::on_parameter_flags_changed);
    connect(parameter, &BaseParameterComponent::started_importing_from, this, &DoubleParameterBox::on_parameter_started_importing);
    connect(parameter, &BaseParameterComponent::stopped_importing_from, this, &DoubleParameterBox::on_parameters_stopped_importing);
    connect(parameter, &FloatParameterComponent::min_changed, this, &DoubleParameterBox::on_parameter_min_changed);
    connect(parameter, &FloatParameterComponent::min_changed, this, &DoubleParameterBox::on_parameter_min_changed);

    if (par->has_flag(BaseParameterComponent::IsUpdateEager))
    {
        connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), par, qOverload<double>(&BaseParameterComponent::set_later));
    }
    else
    {
        connect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
    }
    setEnabled(parameter->has_flag(BaseParameterComponent::IsEditable) && !parameter->is_importing());
}


void DoubleParameterBox::on_parameter_started_importing(BaseParameterComponent *)
{
    setEnabled(false);
}


void DoubleParameterBox::on_parameters_stopped_importing(BaseParameterComponent *)
{
    setEnabled(true);
}


void DoubleParameterBox::on_editing_finished()
{
    parameter->set_later(value());
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
    if ((old_flags & BaseParameterComponent::IsUpdateEager) != (new_flags & BaseParameterComponent::IsUpdateEager))
    {
        if (parameter->has_flag(BaseParameterComponent::IsUpdateEager))
        {
            disconnect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
            connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&BaseParameterComponent::set_later));
        }
        else
        {
            disconnect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&BaseParameterComponent::set_later));
            connect(this, &QAbstractSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
        }
    }
    setEnabled(parameter->has_flag(BaseParameterComponent::IsEditable) && !parameter->is_importing());
}
