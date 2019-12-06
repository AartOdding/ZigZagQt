#pragma once

#include <QDoubleSpinBox>


class BaseComponent;
class Float64Component;



class DoubleParameterBox : public QDoubleSpinBox
{
    Q_OBJECT

public:

    DoubleParameterBox(QWidget * parent, Float64Component * parameter);


public slots:

    void on_parameter_started_importing(BaseComponent * exporter);
    void on_parameters_stopped_importing(BaseComponent * exporter);

    void on_editing_finished();

    void on_parameter_value_changed(double new_value);
    void on_parameter_min_changed(double new_min);
    void on_parameter_max_changed(double new_max);
    void on_parameter_flags_changed(int old_flags, int new_flags);


private:

    Float64Component * parameter;

};
