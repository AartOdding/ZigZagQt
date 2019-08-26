#include "enumwidget.h"



EnumWidget::EnumWidget(QWidget * parent, parameter::Enum* par)
    : QComboBox(parent), parameter(par)
{
    OpenSans.setPixelSize(14);
    setFont(OpenSans);

    for (const auto& value : *(par->definition))
    {
        addItem(value.c_str());
    }

    setCurrentIndex(*par);
    connect(this, qOverload<int>(&QComboBox::currentIndexChanged), par, qOverload<int>(&parameter::Enum::set));
}


/*

    if (parameter->update_mode() == BaseParameter::UpdateMode::AllUpdates)
    {
        connect(this, qOverload<int>(&QSpinBox::valueChanged), par, &IntegerParameter::set);
    }
    else
    {
        connect(this, &QAbstractSpinBox::editingFinished, this, &IntWidget::on_editing_finished);
        connect(this, &IntWidget::has_changed, par, &IntegerParameter::set);
    }*/

/*
void EnumWidget::on_editing_finished()
{
    if (static_cast<int>(*parameter) != value())
    {
        emit has_changed(value());
    }
}*/
