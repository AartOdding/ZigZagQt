#pragma once

#include <vector>

#include <QWidget>
#include <QSpinBox>
#include <QHBoxLayout>

#include "model/parameter/int.h"



class IntWidget : public QWidget
{
    Q_OBJECT

public:

    IntWidget(QWidget * parent, BaseParameter* parameter);


public slots:

    void on_parameters_connected(BaseParameter * exporter, BaseParameter * importer);

    void on_parameters_disconnected(BaseParameter * exporter, BaseParameter * importer);


    void on_editing_finished();

    void on_value_changed(int);


private:

    int num_components;
    BaseParameter* parameter;
    std::vector<QSpinBox*> spinboxes;
    QHBoxLayout layout;
    QFont OpenSans = QFont("Open Sans");

};
