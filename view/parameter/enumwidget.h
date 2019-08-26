#pragma once

#include <QComboBox>

#include "model/parameter/enum.h"




class EnumWidget : public QComboBox
{
    Q_OBJECT

public:

    EnumWidget(QWidget * parent, parameter::Enum* parameter);


    /*
signals:

    void has_changed(int value);

private slots:

    void on_editing_finished();
*/

private:

    parameter::Enum* parameter;
    QFont OpenSans = QFont("Open Sans");


};
