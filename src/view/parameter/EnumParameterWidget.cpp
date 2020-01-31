#include "EnumParameterWidget.hpp"
#include "model/BaseOperator.hpp"



EnumParameterWidget::EnumParameterWidget(QWidget * parent, EnumParameter* par)
    : QComboBox(parent),
      m_enumParameter(par)
{
    auto component = par->getComponents()[0];

    m_flags = component->getFlags();
    m_isImporting = component->isImporting();

    for (const auto& value : par->getPossibleValues())
    {
        addItem(value);
    }

    connect(this, qOverload<int>(&QComboBox::currentIndexChanged),
            component, qOverload<int64_t>(&BaseComponent::importChange), Qt::QueuedConnection);

    connect(component, qOverload<int64_t>(&BaseComponent::exportChange),
            this, &QComboBox::setCurrentIndex, Qt::QueuedConnection);

    connect(component, &BaseComponent::startedImportingFrom,
            this, &EnumParameterWidget::onComponentStartedImporting, Qt::QueuedConnection);

    connect(component, &BaseComponent::stoppedImportingFrom,
            this, &EnumParameterWidget::onComponentStoppedImporting, Qt::QueuedConnection);

    updateEnabledness();
    setCurrentIndex(par->getIndex());
}


void EnumParameterWidget::onComponentStartedImporting(BaseComponent *)
{
    m_isImporting = true;
    updateEnabledness();
}


void EnumParameterWidget::onComponentStoppedImporting(BaseComponent *)
{
    m_isImporting = false;
    updateEnabledness();
}


void EnumParameterWidget::onComponentValueChanged(int value)
{
    if (value >= 0 && value < count())
    {
        setCurrentIndex(value);
    }
}


void EnumParameterWidget::onComponentFlagsChanged(ParameterFlags newFlags)
{
    auto oldFlags = m_flags;
    m_flags = newFlags;

    if (oldFlags.getFlag(ParameterFlag::IsEditable) != newFlags.getFlag(ParameterFlag::IsEditable) ||
        oldFlags.getFlag(ParameterFlag::IsDisabledWhileImporting) != newFlags.getFlag(ParameterFlag::IsDisabledWhileImporting))
    {
        updateEnabledness();
    }
}


void EnumParameterWidget::onEnumChanged(const std::vector<QString>& values)
{
    for (int i = count() - 1; i >= 0; --i)
    {
        removeItem(i);
    }
    for (const QString& value : values)
    {
        addItem(value);
    }
}


void EnumParameterWidget::updateEnabledness()
{
    bool disabled = !m_flags.getFlag(ParameterFlag::IsEditable)
            || (m_isImporting && m_flags.getFlag(ParameterFlag::IsDisabledWhileImporting));

    setEnabled(!disabled);
}
