#pragma once

#include <vector>

#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>

#include "model/parameter/baseparameter.h"



class FloatWidget : public QWidget
{
    Q_OBJECT

public:

    FloatWidget(QWidget * parent, parameter::BaseParameter* parameter);


private slots:

    void on_editing_finished();

    void on_value_changed(int);


private:

    int num_components;
    parameter::BaseParameter* parameter;
    std::vector<QDoubleSpinBox*> spinboxes;
    QHBoxLayout layout;
    QFont OpenSans = QFont("Open Sans");

};
