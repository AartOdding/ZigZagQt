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
    connect(this, qOverload<int>(&QComboBox::currentIndexChanged), component, qOverload<int64_t>(&BaseComponent::store));
    connect(component, qOverload<int64_t>(&BaseComponent::valueChanged), this, &QComboBox::setCurrentIndex);
    connect(component, &BaseComponent::startedImportingFrom, this, &EnumWidget::on_parameter_started_importing);
    connect(component, &BaseComponent::stoppedImportingFrom, this, &EnumWidget::on_parameters_stopped_importing);

    setEnabled(!component->isImporting());
    setCurrentIndex(par->get_index());
}


void EnumWidget::on_parameter_started_importing(BaseComponent *)
{
    setEnabled(false);
}


void EnumWidget::on_parameters_stopped_importing(BaseComponent *)
{
    setEnabled(true);
}
