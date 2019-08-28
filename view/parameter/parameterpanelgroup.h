#pragma once

#include <QWidget>
#include <QFormLayout>


class BaseParameter;
class ParameterOwner;
class ParameterRow;


class ParameterPanelGroup : public QWidget
{
    Q_OBJECT

public:

    explicit ParameterPanelGroup(QWidget *parent, ParameterOwner& group_owner);


private:

    QWidget* new_widget_for_parameter(BaseParameter * parameter);
    QWidget* new_widget_for_row(ParameterRow* parameter_row);

    ParameterOwner * owner;
    QFormLayout layout{ this };

};
