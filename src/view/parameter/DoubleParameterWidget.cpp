#include "model/parameter/Float64Component.hpp"
#include "view/parameter/DoubleParameterWidget.hpp"

#include <numeric>



DoubleParameterWidget::DoubleParameterWidget(QWidget * parent, Float64Component* component)
    : QDoubleSpinBox(parent),
      m_component(component),
      m_flags(component->getFlags()),
      m_isImporting(component->isImporting())
{
    setMinimumWidth(30);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setRange(component->getMin(), component->getMax());
    setValue(component->getValue());
    setSingleStep(0.1);
    updateEnabledness();

    connect(m_component, qOverload<double>(&BaseComponent::exportChange),
            this, &DoubleParameterWidget::onComponentValueChanged, Qt::QueuedConnection);

    connect(m_component, &BaseComponent::flagsChanged,
            this, &DoubleParameterWidget::onComponentFlagsChanged, Qt::QueuedConnection);

    connect(m_component, &BaseComponent::startedImportingFrom,
            this, &DoubleParameterWidget::onComponentStartedImporting, Qt::QueuedConnection);

    connect(m_component, &BaseComponent::stoppedImportingFrom,
            this, &DoubleParameterWidget::onComponentStoppedImporting, Qt::QueuedConnection);

    connect(m_component, &Float64Component::minChanged,
            this, &DoubleParameterWidget::onComponentMinChanged, Qt::QueuedConnection);

    connect(m_component, &Float64Component::maxChanged,
            this, &DoubleParameterWidget::onComponentMaxChanged, Qt::QueuedConnection);

    connect(this, &DoubleParameterWidget::updateComponent,
            component, qOverload<double>(&BaseComponent::importChange), Qt::QueuedConnection);

    connect(this, qOverload<double>(&QDoubleSpinBox::valueChanged),
            this, &DoubleParameterWidget::onSpinBoxValueChanged, Qt::DirectConnection);

    connect(this, &QAbstractSpinBox::editingFinished,
            this, &DoubleParameterWidget::onSpinBoxEditingFinished, Qt::DirectConnection);

}


void DoubleParameterWidget::onComponentStartedImporting(BaseComponent *)
{
    m_isImporting = true;
    updateEnabledness();
}


void DoubleParameterWidget::onComponentStoppedImporting(BaseComponent *)
{
    m_isImporting = false;
    updateEnabledness();
}


void DoubleParameterWidget::onSpinBoxValueChanged(double newValue)
{
    if (m_flags.getFlag(ParameterFlag::UpdatesWhileEditing))
    {
        emit updateComponent(newValue);
    }
}


void DoubleParameterWidget::onSpinBoxEditingFinished()
{
    if (!m_flags.getFlag(ParameterFlag::UpdatesWhileEditing))
    {
        emit updateComponent(value());
    }
}


void DoubleParameterWidget::onComponentValueChanged(double new_value)
{
    setValue(new_value);
}


void DoubleParameterWidget::onComponentMinChanged(double new_min)
{
    setMinimum(new_min);
}


void DoubleParameterWidget::onComponentMaxChanged(double new_max)
{
    setMaximum(new_max);
}


void DoubleParameterWidget::onComponentFlagsChanged(ParameterFlags newFlags)
{
    auto oldFlags = m_flags;
    m_flags = newFlags;

    if (oldFlags.getFlag(ParameterFlag::IsEditable) != newFlags.getFlag(ParameterFlag::IsEditable) ||
        oldFlags.getFlag(ParameterFlag::IsDisabledWhileImporting) != newFlags.getFlag(ParameterFlag::IsDisabledWhileImporting))
    {
        updateEnabledness();
    }
}


void DoubleParameterWidget::updateEnabledness()
{
    bool disabled = !m_flags.getFlag(ParameterFlag::IsEditable)
            || (m_isImporting && m_flags.getFlag(ParameterFlag::IsDisabledWhileImporting));

    setEnabled(!disabled);
}
