#include "enumwidget.h"
#include "model/BaseOperator.hpp"



EnumWidget::EnumWidget(QWidget * parent, EnumParameter* par)
    : QComboBox(parent), parameter(par)
{
    for (const auto& value : *(par->getEnum()))
    {
        addItem(value);
    }
    auto component = par->getComponents()[0];//(0);
    connect(this, qOverload<int>(&QComboBox::currentIndexChanged), component, qOverload<int64_t>(&BaseComponent::change));
    connect(component, qOverload<int64_t>(&BaseComponent::valueChanged), this, &QComboBox::setCurrentIndex);
    connect(component, &BaseComponent::startedImportingFrom, this, &EnumWidget::on_parameter_started_importing);
    connect(component, &BaseComponent::stoppedImportingFrom, this, &EnumWidget::on_parameters_stopped_importing);

    setEnabled(!component->isImporting());
    setCurrentIndex(par->getIndex());
}


void EnumWidget::on_parameter_started_importing(BaseComponent *)
{
    setEnabled(false);
}


void EnumWidget::on_parameters_stopped_importing(BaseComponent *)
{
    setEnabled(true);
}
