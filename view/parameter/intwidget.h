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


public slots:

    void on_parameter_started_importing(BaseParameter * exporter);

    void on_parameters_stopped_importing(BaseParameter * exporter);


    void on_editing_finished();

    void on_value_changed_to(int);

    void on_value_changed();


private:

    int num_components;
    BaseParameter* parameter;
    std::vector<QSpinBox*> spinboxes;
    QHBoxLayout layout;
    QFont OpenSans = QFont("Open Sans");

};
