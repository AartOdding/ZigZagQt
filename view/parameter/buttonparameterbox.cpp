#include "buttonparameterbox.h"
#include "model/parameter/buttonparameter.h"


ButtonParameterBox::ButtonParameterBox(QWidget * parent, ButtonPar* b)
    : QPushButton(b->getName(), parent), button(b)
{
    setAutoDefault(false);
    setAutoRepeat(false);
    connect(this, &QAbstractButton::clicked, this, &ButtonParameterBox::on_button_clicked);
}


void ButtonParameterBox::on_button_clicked()
{
    button->getComponents()[0]->change(static_cast<int64_t>(1));
}
