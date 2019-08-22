#pragma once

#include <QSpinBox>
#include "model/parameter/integerparameter.h"



class IntWidget : public QSpinBox
{
    Q_OBJECT

public:

    IntWidget(QWidget * parent, IntegerParameter* parameter);


signals:

    void has_changed(int value);


private slots:

    void on_editing_finished();


private:

    IntegerParameter* parameter;
    QFont OpenSans = QFont("Open Sans");


};
