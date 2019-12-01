#pragma once

#include <QComboBox>

#include "model/parameter/enumparameter.h"


class BaseComponent;
class IntParameterComponent;



class EnumWidget : public QComboBox
{
    Q_OBJECT

public:

    EnumWidget(QWidget * parent, EnumPar* parameter);

private slots:

    void on_parameter_started_importing(BaseComponent *);
    void on_parameters_stopped_importing(BaseComponent *);

private:

    EnumPar* parameter;

};
