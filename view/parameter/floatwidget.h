#pragma once

#include <vector>

#include <QWidget>
#include <QHBoxLayout>
#include <QDoubleSpinBox>

#include "model/parameter/float.h"



class FloatWidget : public QWidget
{
    Q_OBJECT

public:

    FloatWidget(QWidget * parent, BaseParameter* parameter);


public slots:

    void on_parameter_started_importing(BaseParameter * exporter);

    void on_parameters_stopped_importing(BaseParameter * exporter);


    void on_editing_finished();

    void on_value_changed(int);


private:

    int num_components;
    BaseParameter* parameter;
    std::vector<QDoubleSpinBox*> spinboxes;
    QHBoxLayout layout;
    QFont OpenSans = QFont("Open Sans");

};
