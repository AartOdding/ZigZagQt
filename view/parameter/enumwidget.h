#pragma once

#include <QComboBox>

#include "model/parameter/enumparameter.h"


class ParameterComponent;
class ParameterComponentInt64;



class EnumWidget : public QComboBox
{
    Q_OBJECT

public:

    EnumWidget(QWidget * parent, EnumPar* parameter);

private slots:

    void on_parameter_started_importing(ParameterComponent *);
    void on_parameters_stopped_importing(ParameterComponent *);

private:

    EnumPar* parameter;

};
