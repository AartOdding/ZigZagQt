#include "enumwidget.h"
#include "model/parameter/parameterowner.h"



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

    auto op = parameter->owner()->top_level_owner();
    connect(op, &ParameterOwner::parameters_connected, this, &EnumWidget::on_parameters_connected);
    connect(op, &ParameterOwner::parameters_disconnected, this, &EnumWidget::on_parameters_disconnected);
    setEnabled(!parameter->is_importing());
}


void EnumWidget::on_parameters_connected(BaseParameter * exporter, BaseParameter * importer)
{
    if (importer == parameter)
    {
        setEnabled(false);
    }
}


void EnumWidget::on_parameters_disconnected(BaseParameter * exporter, BaseParameter * importer)
{
    if (importer == parameter)
    {
        setEnabled(true);
    }
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
