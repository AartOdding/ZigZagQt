#pragma once

#include <QPushButton>


class ButtonParameter;



class ButtonParameterBox : public QPushButton
{
    Q_OBJECT

public:

    ButtonParameterBox(QWidget * parent, ButtonParameter* button);

public slots:

    void on_button_clicked();

private:

    ButtonParameter* button;

};
