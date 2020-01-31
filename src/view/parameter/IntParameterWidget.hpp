#pragma once

#include <QSpinBox>
#include "model/parameter/ParameterFlags.hpp"

class BaseComponent;
class Int64Component;



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

class IntParameterWidget : public QSpinBox
{
    Q_OBJECT

public:

    IntParameterWidget(QWidget * parent, Int64Component * component);


public slots:

    void onComponentStartedImporting(BaseComponent * exporter);
    void onComponentStoppedImporting(BaseComponent * exporter);

    void onSpinBoxValueChanged(int newValue);
    void onSpinBoxEditingFinished();

    void onComponentValueChanged(int64_t newValue);
    void onComponentMinChanged(int64_t newMin);
    void onComponentMaxChanged(int64_t newMax);
    void onComponentFlagsChanged(ParameterFlags newFlags);

signals:

    void updateComponent(int value);

private:

    void updateEnabledness();

    Int64Component * m_component;
    ParameterFlags m_flags;
    bool m_isImporting;

};
