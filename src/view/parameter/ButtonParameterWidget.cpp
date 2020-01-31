#include "ButtonParameterWidget.hpp"
#include "model/parameter/ButtonParameter.hpp"


ButtonParameterWidget::ButtonParameterWidget(QWidget * parent, ButtonParameter* b)
    : QPushButton(b->objectName(), parent),
      m_button(b)
{
    m_flags = b->getTriggerComponent()->getFlags();
    m_isImporting = b->getTriggerComponent()->isImporting();

    setAutoDefault(false);
    setAutoRepeat(false);
    updateEnabledness();

    connect(this, &QAbstractButton::clicked,
            b->getTriggerComponent(), qOverload<>(&TriggerComponent::importChange), Qt::QueuedConnection);

    connect(b->getTriggerComponent(), &BaseComponent::flagsChanged,
            this, &ButtonParameterWidget::onComponentFlagsChanged, Qt::QueuedConnection);

    connect(b->getTriggerComponent(), &BaseComponent::startedImportingFrom,
            this, &ButtonParameterWidget::onComponentStartedImporting, Qt::QueuedConnection);

    connect(b->getTriggerComponent(), &BaseComponent::stoppedImportingFrom,
            this, &ButtonParameterWidget::onComponentStoppedImporting, Qt::QueuedConnection);
}


void ButtonParameterWidget::onComponentStartedImporting(BaseComponent *)
{
    m_isImporting = true;
    updateEnabledness();
}


void ButtonParameterWidget::onComponentStoppedImporting(BaseComponent *)
{
    m_isImporting = false;
    updateEnabledness();
}


void ButtonParameterWidget::onComponentFlagsChanged(ParameterFlags newFlags)
{
    auto oldFlags = m_flags;
    m_flags = newFlags;

    if (oldFlags.getFlag(ParameterFlag::IsEditable) != newFlags.getFlag(ParameterFlag::IsEditable) ||
        oldFlags.getFlag(ParameterFlag::IsDisabledWhileImporting) != newFlags.getFlag(ParameterFlag::IsDisabledWhileImporting))
    {
        updateEnabledness();
    }
}


void ButtonParameterWidget::updateEnabledness()
{
    bool disabled = !m_flags.getFlag(ParameterFlag::IsEditable)
            || (m_isImporting && m_flags.getFlag(ParameterFlag::IsDisabledWhileImporting));

    setEnabled(!disabled);
}
