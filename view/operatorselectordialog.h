#pragma once

#include <QFont>
#include <QWidget>

#include "ui_librarydialogpanel.h"


class Viewport;


class OperatorSelectorDialog : public QWidget
{
public:

    OperatorSelectorDialog(Viewport* viewport);

protected:



private:

    Ui::OperatorSelectorForm ui;

    QFont MontSerrat{ "MontSerrat" };


};
