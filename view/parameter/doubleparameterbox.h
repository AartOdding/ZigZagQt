#pragma once

#include <QDoubleSpinBox>


class ParameterComponent;
class ParameterComponentDouble;



class DoubleParameterBox : public QDoubleSpinBox
{
    Q_OBJECT

public:

    DoubleParameterBox(QWidget * parent, ParameterComponentDouble * parameter);


public slots:

    void on_parameter_started_importing(ParameterComponent * exporter);
    void on_parameters_stopped_importing(ParameterComponent * exporter);

    void on_editing_finished();

    void on_parameter_value_changed(double new_value);
    void on_parameter_min_changed(double new_min);
    void on_parameter_max_changed(double new_max);
    void on_parameter_update_eager_changed(bool is_eager);


private:

    ParameterComponentDouble * parameter;

};
