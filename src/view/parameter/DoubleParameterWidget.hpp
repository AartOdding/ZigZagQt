#pragma once

#include <QDoubleSpinBox>
#include "model/parameter/ParameterFlags.hpp"

class BaseComponent;
class Float64Component;



/*
 * During the call to the constructor the operator that owns the connected component shall
 * be locked. because of this it is safe to call get-like functions on the component.
 *
 * After construction it is not gauranteed that the belonging operator is locked.
 * thus is not allowed to directly call any functions on the operaotr or component.
 *
 * When parts of the operator object tree are deleted it has to be done by the gui thread.
 * because of this the view will always know before the model that it is going to be
 * deleted. because of this as long as this widget still exists it can be assumed
 * the connected to component still exists.
 */

class DoubleParameterWidget : public QDoubleSpinBox
{
    Q_OBJECT

public:

    DoubleParameterWidget(QWidget * parent, Float64Component * m_component);


public slots:

    void onComponentStartedImporting(BaseComponent * exporter);
    void onComponentStoppedImporting(BaseComponent * exporter);

    void onSpinBoxValueChanged(double newValue);
    void onSpinBoxEditingFinished();

    void onComponentValueChanged(double newValue);
    void onComponentMinChanged(double newMin);
    void onComponentMaxChanged(double newMax);
    void onComponentFlagsChanged(ParameterFlags newFlags);

signals:

    void updateComponent(double value);

private:

    void updateEnabledness();

    Float64Component * m_component;
    ParameterFlags m_flags;
    bool m_isImporting;

};
