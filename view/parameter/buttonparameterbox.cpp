#include "buttonparameterbox.h"
#include "model/parameter/ButtonParameter.hpp"


ButtonParameterBox::ButtonParameterBox(QWidget * parent, ButtonPar* b)
    : QPushButton(b->objectName(), parent), button(b)
{
    setAutoDefault(false);
    setAutoRepeat(false);
    connect(this, &QAbstractButton::clicked, this, &ButtonParameterBox::on_button_clicked);
}


void ButtonParameterBox::on_button_clicked()
{
    button->getComponents()[0]->change(static_cast<int64_t>(1));
}
