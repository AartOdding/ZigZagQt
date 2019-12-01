#include "buttonparameterbox.h"
#include "model/parameter/buttonparameter.h"


ButtonParameterBox::ButtonParameterBox(QWidget * parent, ButtonPar* b)
    : QPushButton(b->get_name(), parent), button(b)
{
    setAutoDefault(false);
    setAutoRepeat(false);
    connect(this, &QAbstractButton::clicked, this, &ButtonParameterBox::on_button_clicked);
}


void ButtonParameterBox::on_button_clicked()
{
    button->get_component(0)->set(static_cast<int64_t>(1));
}
