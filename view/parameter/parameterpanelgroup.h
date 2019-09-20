#pragma once

#include <QFrame>
#include <QFormLayout>


class BaseParameter;
class ParameterOwner;
class ParameterRow;


class ParameterPanelGroup : public QFrame
{
    Q_OBJECT

public:

    explicit ParameterPanelGroup(QWidget *parent, ParameterOwner* parameters);


private:

    QWidget* new_widget_for_parameter(BaseParameter * parameter);

    ParameterOwner * parameter_owner;
    QFormLayout layout{ this };

};
