#include "int64parameterbox.h"
#include "model/parameter/intparametercomponent.h"
#include "utility/numeric.h"

#include <numeric>


Int64ParameterBox::Int64ParameterBox(QWidget * parent, IntParameterComponent* par)
    : QSpinBox(parent), parameter(par)
{
    Q_ASSERT(par);

    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setMinimum(largest<int64_t>(par->get_min(), std::numeric_limits<int>::min()));
    setMaximum(smallest<int64_t>(par->get_max(), std::numeric_limits<int>::max()));
    setValue(par->get());
    setEnabled(!parameter->is_importing());

    connect(parameter, qOverload<int64_t>(&BaseParameterComponent::value_changed), this, &Int64ParameterBox::on_parameter_changed);

    connect(parameter, &BaseParameterComponent::flags_changed, this, &Int64ParameterBox::on_parameter_flags_changed);
    connect(parameter, &BaseParameterComponent::started_importing_from, this, &Int64ParameterBox::on_parameter_started_importing);
    connect(parameter, &BaseParameterComponent::stopped_importing_from, this, &Int64ParameterBox::on_parameters_stopped_importing);
    connect(parameter, &IntParameterComponent::min_changed, this, &Int64ParameterBox::on_parameter_min_changed);
    connect(parameter, &IntParameterComponent::min_changed, this, &Int64ParameterBox::on_parameter_min_changed);

    if (par->has_flag(BaseParameterComponent::IsUpdateEager))
    {
        connect(this, qOverload<int>(&QSpinBox::valueChanged), par, qOverload<int64_t>(&BaseParameterComponent::set_later));
    }
    else
    {
        connect(this, &QAbstractSpinBox::editingFinished, this, &Int64ParameterBox::on_editing_finished);
    }
}


void Int64ParameterBox::on_parameter_started_importing(BaseParameterComponent *)
{
    setEnabled(false);
}


void Int64ParameterBox::on_parameters_stopped_importing(BaseParameterComponent *)
{
    setEnabled(true);
}


void Int64ParameterBox::on_editing_finished()
{
    parameter->set_later(static_cast<int64_t>(value()));
}


void Int64ParameterBox::on_parameter_changed(int64_t new_value)
{
    setValue(constrain<int64_t>(new_value, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
}


void Int64ParameterBox::on_parameter_min_changed(int64_t new_min)
{
    setMinimum(largest<int64_t>(new_min, std::numeric_limits<int>::min()));
}


void Int64ParameterBox::on_parameter_max_changed(int64_t new_max)
{
    setMaximum(smallest<int64_t>(new_max, std::numeric_limits<int>::max()));
}


void Int64ParameterBox::on_parameter_flags_changed(int old_flags, int new_flags)
{
    if ((old_flags & BaseParameterComponent::IsUpdateEager) != (new_flags & BaseParameterComponent::IsUpdateEager))
    {
        if (parameter->has_flag(BaseParameterComponent::IsUpdateEager))
        {
            disconnect(this, &QAbstractSpinBox::editingFinished, this, &Int64ParameterBox::on_editing_finished);
            connect(this, qOverload<int>(&QSpinBox::valueChanged), parameter, qOverload<int64_t>(&BaseParameterComponent::set_later));
        }
        else
        {
            disconnect(this, qOverload<int>(&QSpinBox::valueChanged), parameter, qOverload<int64_t>(&BaseParameterComponent::set_later));
            connect(this, &QAbstractSpinBox::editingFinished, this, &Int64ParameterBox::on_editing_finished);
        }
    }
    setEnabled(parameter->has_flag(BaseParameterComponent::IsEditable) && !parameter->is_importing());
}
