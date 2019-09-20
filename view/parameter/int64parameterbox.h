#pragma once

#include <QSpinBox>


class ParameterComponent;
class ParameterComponentInt64;



class Int64ParameterBox : public QSpinBox
{
    Q_OBJECT

public:

    Int64ParameterBox(QWidget * parent, ParameterComponentInt64 * parameter);


public slots:

    void on_parameter_started_importing(ParameterComponent * exporter);
    void on_parameters_stopped_importing(ParameterComponent * exporter);

    void on_editing_finished();

    void on_parameter_changed(int64_t new_value);
    void on_parameter_min_changed(int64_t new_min);
    void on_parameter_max_changed(int64_t new_max);
    void on_parameter_update_eager_changed(bool is_eager);


private:

    ParameterComponentInt64 * parameter;

};
