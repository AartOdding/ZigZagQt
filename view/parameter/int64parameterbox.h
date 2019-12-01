#pragma once

#include <QSpinBox>


class BaseComponent;
class IntParameterComponent;



class Int64ParameterBox : public QSpinBox
{
    Q_OBJECT

public:

    Int64ParameterBox(QWidget * parent, IntParameterComponent * parameter);


public slots:

    void on_parameter_started_importing(BaseComponent * exporter);
    void on_parameters_stopped_importing(BaseComponent * exporter);

    void on_editing_finished();

    void on_parameter_changed(int64_t new_value);
    void on_parameter_min_changed(int64_t new_min);
    void on_parameter_max_changed(int64_t new_max);
    void on_parameter_flags_changed(int old_flags, int new_flags);


private:

    IntParameterComponent * parameter;

};
