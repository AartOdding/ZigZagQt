#include "doubleparameterbox.h"
#include "model/parameter/parametercomponentdouble.h"
#include "utility/numeric.h"

#include <numeric>


DoubleParameterBox::DoubleParameterBox(QWidget * parent, ParameterComponentDouble* par)
    : QDoubleSpinBox(parent), parameter(par)
{
    Q_ASSERT(par);

    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setRange(par->get_min(), par->get_max());
    setValue(par->get());
    setSingleStep(0.1);
    setEnabled(!parameter->is_importing());

    connect(parameter, qOverload<double>(&ParameterComponent::value_changed), this, &DoubleParameterBox::on_parameter_value_changed);

    connect(parameter, &ParameterComponent::started_importing_from, this, &DoubleParameterBox::on_parameter_started_importing);
    connect(parameter, &ParameterComponent::stopped_importing_from, this, &DoubleParameterBox::on_parameters_stopped_importing);
    connect(parameter, &ParameterComponentDouble::min_changed, this, &DoubleParameterBox::on_parameter_min_changed);
    connect(parameter, &ParameterComponentDouble::min_changed, this, &DoubleParameterBox::on_parameter_min_changed);

    if (par->get_update_eager())
    {
        connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), par, qOverload<double>(&ParameterComponent::set_later));
    }
    else
    {
        connect(this, &QSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
    }
}


void DoubleParameterBox::on_parameter_started_importing(ParameterComponent *)
{
    setEnabled(false);
}


void DoubleParameterBox::on_parameters_stopped_importing(ParameterComponent *)
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


void DoubleParameterBox::on_parameter_update_eager_changed(bool is_eager)
{
    if (is_eager)
    {
        disconnect(this, &QSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
        connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&ParameterComponent::set_later));
    }
    else
    {
        disconnect(this, qOverload<double>(&QDoubleSpinBox::valueChanged), parameter, qOverload<double>(&ParameterComponent::set_later));
        connect(this, &QSpinBox::editingFinished, this, &DoubleParameterBox::on_editing_finished);
    }
}
