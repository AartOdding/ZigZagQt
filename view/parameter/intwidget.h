#pragma once

#include <vector>

#include <QWidget>
#include <QSpinBox>
#include <QHBoxLayout>

#include "model/parameter/int.h"



class IntWidget : public QWidget
{
    Q_OBJECT

public:

    IntWidget(QWidget * parent, BaseParameter* parameter);


private slots:

    void on_editing_finished();

    void on_value_changed(int);


private:

    int num_components;
    BaseParameter* parameter;
    std::vector<QSpinBox*> spinboxes;
    QHBoxLayout layout;
    QFont OpenSans = QFont("Open Sans");

};
