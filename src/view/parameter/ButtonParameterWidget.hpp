#pragma once

#include <QPushButton>
#include "model/parameter/ParameterFlags.hpp"


class BaseComponent;
class ButtonParameter;


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

class ButtonParameterWidget : public QPushButton
{
    Q_OBJECT

public:

    ButtonParameterWidget(QWidget * parent, ButtonParameter* m_button);

public slots:

    void onComponentStartedImporting(BaseComponent * exporter);
    void onComponentStoppedImporting(BaseComponent * exporter);

    void onComponentFlagsChanged(ParameterFlags newFlags);

private:

    void updateEnabledness();

    ButtonParameter* m_button;
    ParameterFlags m_flags;
    bool m_isImporting;

};
