#pragma once

#include <QSpinBox>
#include "model/parameter/BaseComponent.hpp"


class BaseComponent;
class Int64Component;



class Int64ParameterBox : public QSpinBox
{
    Q_OBJECT

public:

    Int64ParameterBox(QWidget * parent, Int64Component * parameter);


public slots:

    void on_parameter_started_importing(BaseComponent * exporter);
    void on_parameters_stopped_importing(BaseComponent * exporter);

    void on_editing_finished();

    void on_parameterChangeEvent(int64_t new_value);
    void on_parameter_min_changed(int64_t new_min);
    void on_parameter_max_changed(int64_t new_max);

    void onFlagsChanged(ParameterFlags flag, bool value);

private:

    Int64Component * parameter;

};
