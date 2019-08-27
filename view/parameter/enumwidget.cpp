#include "enumwidget.h"



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
