#include "enumwidget.h"
#include "model/baseoperator.h"



EnumWidget::EnumWidget(QWidget * parent, EnumPar* par)
    : QComboBox(parent), parameter(par)
{
    for (const auto& value : *(par->get_enum()))
    {
        addItem(value);
    }
    auto component = par->get_component(0);
    connect(this, qOverload<int>(&QComboBox::currentIndexChanged), component, qOverload<int64_t>(&BaseParameterComponent::set_later));
    connect(component, qOverload<int64_t>(&BaseParameterComponent::value_changed), this, &QComboBox::setCurrentIndex);
    connect(component, &BaseParameterComponent::started_importing_from, this, &EnumWidget::on_parameter_started_importing);
    connect(component, &BaseParameterComponent::stopped_importing_from, this, &EnumWidget::on_parameters_stopped_importing);

    setEnabled(!component->is_importing());
    setCurrentIndex(par->get_index());
}


void EnumWidget::on_parameter_started_importing(BaseParameterComponent *)
{
    setEnabled(false);
}


void EnumWidget::on_parameters_stopped_importing(BaseParameterComponent *)
{
    setEnabled(true);
}
