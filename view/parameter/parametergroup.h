#pragma once

#include <QFrame>
#include <QFormLayout>


class BaseParameter;
class ParameterOwner;
class ParameterRow;


class ParameterGroup : public QFrame
{
    Q_OBJECT

public:

    ParameterGroup(QWidget *parent, BaseParameter* parameters);


private:

    QWidget* new_widget_for_parameter(BaseParameter * parameter);

    BaseParameter * parameters;
    QFormLayout layout{ this };

};
