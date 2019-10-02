#pragma once

#include <QComboBox>

#include "model/parameter/enumparameter.h"


class BaseParameterComponent;
class IntParameterComponent;



class EnumWidget : public QComboBox
{
    Q_OBJECT

public:

    EnumWidget(QWidget * parent, EnumPar* parameter);

private slots:

    void on_parameter_started_importing(BaseParameterComponent *);
    void on_parameters_stopped_importing(BaseParameterComponent *);

private:

    EnumPar* parameter;

};
