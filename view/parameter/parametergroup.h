#pragma once

#include <QFrame>
#include <QFormLayout>


class BaseParameterOld;
class ParameterOwner;
class ParameterRow;


class ParameterGroup : public QFrame
{
    Q_OBJECT

public:

    ParameterGroup(QWidget *parent, BaseParameterOld* parameters);


private:

    QWidget* new_widget_for_parameter(BaseParameterOld * parameter);

    BaseParameterOld * parameters;
    QFormLayout layout{ this };

};
