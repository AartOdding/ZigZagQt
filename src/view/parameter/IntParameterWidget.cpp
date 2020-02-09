#include "model/parameter/Int64Component.hpp"
#include "utility/numericHelpers.hpp"
#include "view/parameter/IntParameterWidget.hpp"

#include <numeric>




IntParameterWidget::IntParameterWidget(QWidget * parent, Int64Component* component)
    : QSpinBox(parent),
      m_component(component),
      m_flags(component->getFlags()),
      m_isImporting(component->isImporting())
{
    setMinimumWidth(30);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    setButtonSymbols(QAbstractSpinBox::NoButtons);
    setMinimum(largest<int64_t>(component->getMin(), std::numeric_limits<int>::min()));
    setMaximum(smallest<int64_t>(component->getMax(), std::numeric_limits<int>::max()));
    setValue(component->getValue());
    updateEnabledness();

    connect(m_component, qOverload<int64_t>(&BaseComponent::exportChange),
            this, &IntParameterWidget::onComponentValueChanged, Qt::QueuedConnection);

    connect(m_component, &BaseComponent::flagsChanged,
            this, &IntParameterWidget::onComponentFlagsChanged, Qt::QueuedConnection);

    connect(m_component, &BaseComponent::startedImportingFrom,
            this, &IntParameterWidget::onComponentStartedImporting, Qt::QueuedConnection);

    connect(m_component, &BaseComponent::stoppedImportingFrom,
            this, &IntParameterWidget::onComponentStoppedImporting, Qt::QueuedConnection);

    connect(m_component, &Int64Component::minChanged,
            this, &IntParameterWidget::onComponentMinChanged, Qt::QueuedConnection);

    connect(m_component, &Int64Component::maxChanged,
            this, &IntParameterWidget::onComponentMaxChanged, Qt::QueuedConnection);

    connect(this, &IntParameterWidget::updateComponent,
            component, qOverload<int64_t>(&BaseComponent::importChange), Qt::QueuedConnection);

    connect(this, qOverload<int>(&QSpinBox::valueChanged),
            this, &IntParameterWidget::onSpinBoxValueChanged, Qt::DirectConnection);

    connect(this, &QAbstractSpinBox::editingFinished,
            this, &IntParameterWidget::onSpinBoxEditingFinished, Qt::DirectConnection);
}


void IntParameterWidget::onComponentStartedImporting(BaseComponent *)
{
    m_isImporting = true;
    updateEnabledness();
}


void IntParameterWidget::onComponentStoppedImporting(BaseComponent *)
{
    m_isImporting = false;
    updateEnabledness();
}


void IntParameterWidget::onSpinBoxValueChanged(int newValue)
{
    if (m_flags.getFlag(ParameterFlag::UpdatesWhileEditing))
    {
        emit updateComponent(newValue);
    }
}


void IntParameterWidget::onSpinBoxEditingFinished()
{
    if (!m_flags.getFlag(ParameterFlag::UpdatesWhileEditing))
    {
        emit updateComponent(value());
    }
}


void IntParameterWidget::onComponentValueChanged(int64_t new_value)
{
    setValue(constrain<int64_t>(new_value, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
}


void IntParameterWidget::onComponentMinChanged(int64_t new_min)
{
    setMinimum(largest<int64_t>(new_min, std::numeric_limits<int>::min()));
}


void IntParameterWidget::onComponentMaxChanged(int64_t new_max)
{
    setMaximum(smallest<int64_t>(new_max, std::numeric_limits<int>::max()));
}


void IntParameterWidget::onComponentFlagsChanged(ParameterFlags newFlags)
{
    auto oldFlags = m_flags;
    m_flags = newFlags;

    if (oldFlags.getFlag(ParameterFlag::IsEditable) != newFlags.getFlag(ParameterFlag::IsEditable) ||
        oldFlags.getFlag(ParameterFlag::IsDisabledWhileImporting) != newFlags.getFlag(ParameterFlag::IsDisabledWhileImporting))
    {
        updateEnabledness();
    }
}


void IntParameterWidget::updateEnabledness()
{
    bool disabled = !m_flags.getFlag(ParameterFlag::IsEditable)
            || (m_isImporting && m_flags.getFlag(ParameterFlag::IsDisabledWhileImporting));

    setEnabled(!disabled);
}

