#pragma once

#include <QFrame>
#include <QFormLayout>


class BaseZigZagObject;
class BaseParameter;
class ParameterOwner;
class ParameterRow;


class ParameterGroup : public QFrame
{
    Q_OBJECT

public:

    ParameterGroup(QWidget *parent, BaseZigZagObject* parameters);


private:

    QWidget* new_widget_for_parameter(BaseParameter * parameter);

    BaseZigZagObject * parameters;
    QFormLayout layout{ this };

};
