#pragma once

#include <QComboBox>

#include "model/parameter/EnumParameter.hpp"


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

class EnumParameterWidget : public QComboBox
{
    Q_OBJECT

public:

    EnumParameterWidget(QWidget * parent, EnumParameter* m_enumParameter);

private slots:

    void onComponentStartedImporting(BaseComponent *);
    void onComponentStoppedImporting(BaseComponent *);

    void onComponentValueChanged(int value);
    void onComponentFlagsChanged(ParameterFlags newFlags);

    void onEnumChanged(const std::vector<QString>& values);

private:

    void updateEnabledness();

    EnumParameter* m_enumParameter;
    ParameterFlags m_flags;
    bool m_isImporting;

};
