#pragma once

#include <QComboBox>

#include "model/parameter/EnumParameter.hpp"


class BaseComponent;
class Int64Component;



class EnumWidget : public QComboBox
{
    Q_OBJECT

public:

    EnumWidget(QWidget * parent, EnumParameter* parameter);

private slots:

    void on_parameter_started_importing(BaseComponent *);
    void on_parameters_stopped_importing(BaseComponent *);

private:

    EnumParameter* parameter;

};
