#include "enumwidget.h"
#include "model/baseoperator.h"



EnumWidget::EnumWidget(QWidget * parent, EnumPar* par)
    : QComboBox(parent), parameter(par)
{
    OpenSans.setPixelSize(14);
    setFont(OpenSans);

    for (const auto& value : *(par->definition))
    {
        addItem(value.c_str());
    }

    setCurrentIndex(*par);
    connect(this, qOverload<int>(&QComboBox::currentIndexChanged), this, &EnumWidget::on_index_changed);

    connect(parameter, &BaseParameter::started_importing_from, this, &EnumWidget::on_parameter_started_importing);
    connect(parameter, &BaseParameter::stopped_importing_from, this, &EnumWidget::on_parameters_stopped_importing);
    setEnabled(!parameter->is_importing());
}


void EnumWidget::on_parameter_started_importing(BaseParameter * exporter)
{
    setEnabled(false);
}


void EnumWidget::on_parameters_stopped_importing(BaseParameter * exporter)
{
    setEnabled(true);
}


void EnumWidget::on_index_changed(int new_index)
{
    parameter->set(new_index);
}
/*

    if (parameter->update_mode() == BaseUpdateMode::AllUpdates)
    {
        connect(this, qOverload<int>(&QSpinBox::valueChanged), par, &Integerset);
    }
    else
    {
        connect(this, &QAbstractSpinBox::editingFinished, this, &IntWidget::on_editing_finished);
        connect(this, &IntWidget::has_changed, par, &Integerset);
    }*/

/*
void EnumWidget::on_editing_finished()
{
    if (static_cast<int>(*parameter) != value())
    {
        emit has_changed(value());
    }
}*/
