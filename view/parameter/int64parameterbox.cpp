#include "int64parameterbox.h"
#include "model/parameter/Int64Component.hpp"
#include "utility/numeric.h"

#include <numeric>


Int64ParameterBox::Int64ParameterBox(QWidget * parent, Int64Component* par)
    : QSpinBox(parent), parameter(par)
{
    Q_ASSERT(par);

    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setMinimum(largest<int64_t>(par->getMin(), std::numeric_limits<int>::min()));
    setMaximum(smallest<int64_t>(par->getMax(), std::numeric_limits<int>::max()));
    setValue(par->getValue());
    setEnabled(!parameter->isImporting());

    connect(parameter, qOverload<int64_t>(&BaseComponent::valueChanged), this, &Int64ParameterBox::on_parameter_changed);

    connect(parameter, &BaseComponent::flagChanged, this, &Int64ParameterBox::on_parameter_flags_changed);
    connect(parameter, &BaseComponent::startedImportingFrom, this, &Int64ParameterBox::on_parameter_started_importing);
    connect(parameter, &BaseComponent::stoppedImportingFrom, this, &Int64ParameterBox::on_parameters_stopped_importing);
    connect(parameter, &Int64Component::minChanged, this, &Int64ParameterBox::on_parameter_min_changed);
    connect(parameter, &Int64Component::minChanged, this, &Int64ParameterBox::on_parameter_min_changed);

    if (!par->hasFlag(BaseComponent::MinimalUpdates))
    {
        connect(this, qOverload<int>(&QSpinBox::valueChanged), par, qOverload<int64_t>(&BaseComponent::change));
    }
    else
    {
        connect(this, &QAbstractSpinBox::editingFinished, this, &Int64ParameterBox::on_editing_finished);
    }
}


void Int64ParameterBox::on_parameter_started_importing(BaseComponent *)
{
    setEnabled(false);
}


void Int64ParameterBox::on_parameters_stopped_importing(BaseComponent *)
{
    setEnabled(true);
}


void Int64ParameterBox::on_editing_finished()
{
    parameter->change(static_cast<int64_t>(value()));
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
    if ((old_flags & BaseComponent::MinimalUpdates) != (new_flags & BaseComponent::MinimalUpdates))
    {
        if (!parameter->hasFlag(BaseComponent::MinimalUpdates))
        {
            disconnect(this, &QAbstractSpinBox::editingFinished, this, &Int64ParameterBox::on_editing_finished);
            connect(this, qOverload<int>(&QSpinBox::valueChanged), parameter, qOverload<int64_t>(&BaseComponent::change));
        }
        else
        {
            disconnect(this, qOverload<int>(&QSpinBox::valueChanged), parameter, qOverload<int64_t>(&BaseComponent::change));
            connect(this, &QAbstractSpinBox::editingFinished, this, &Int64ParameterBox::on_editing_finished);
        }
    }
    setEnabled(parameter->hasFlag(BaseComponent::IsEditable) && !parameter->isImporting());
}
