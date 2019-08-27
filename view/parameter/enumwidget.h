#pragma once

#include <QComboBox>

#include "model/parameter/enum.h"




class EnumWidget : public QComboBox
{
    Q_OBJECT

public:

    EnumWidget(QWidget * parent, EnumPar* parameter);



private slots:

    void on_index_changed(int new_index);


private:

    EnumPar* parameter;
    QFont OpenSans = QFont("Open Sans");


};
