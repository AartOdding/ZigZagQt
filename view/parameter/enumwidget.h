#pragma once

#include <QComboBox>

#include "model/parameter/enumparameter.h"




class EnumWidget : public QComboBox
{
    Q_OBJECT

public:

    EnumWidget(QWidget * parent, EnumParameter* parameter);


    /*
signals:

    void has_changed(int value);

private slots:

    void on_editing_finished();
*/

private:

    EnumParameter* parameter;
    QFont OpenSans = QFont("Open Sans");


};
