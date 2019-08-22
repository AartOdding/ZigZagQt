#include "intwidget.h"



IntWidget::IntWidget(QWidget * parent, IntegerParameter* par)
    : QSpinBox(parent), parameter(par)
{
    OpenSans.setPixelSize(14);
    setFont(OpenSans);

    setRange(INT_MIN, INT_MAX); // TODO: set to limits of parameter
    setValue(*parameter);
    setButtonSymbols(QAbstractSpinBox::NoButtons);

    if (parameter->update_mode() == BaseParameter::UpdateMode::AllUpdates)
    {
        connect(this, qOverload<int>(&QSpinBox::valueChanged), par, &IntegerParameter::set);
    }
    else
    {
        connect(this, &QAbstractSpinBox::editingFinished, this, &IntWidget::on_editing_finished);
        connect(this, &IntWidget::has_changed, par, &IntegerParameter::set);
    }
}


void IntWidget::on_editing_finished()
{
    if (static_cast<int>(*parameter) != value())
    {
        emit has_changed(value());
    }
}
