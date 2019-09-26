#pragma once

#include <QPushButton>


class ButtonPar;



class ButtonParameterBox : public QPushButton
{
    Q_OBJECT

public:

    ButtonParameterBox(QWidget * parent, ButtonPar* button);

public slots:

    void on_button_clicked();

private:

    ButtonPar* button;

};
