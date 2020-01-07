#include "TriggerComponent.hpp"




TriggerComponent::TriggerComponent(BaseParameter* parameter)
    : BaseComponent(parameter)
{

}



bool TriggerComponent::update()
{
    if (m_triggerReceived)
    {
        m_triggerReceived = false;
        emit valueChanged();
        return true;
    }
    return false;
}


void TriggerComponent::change()
{
    m_triggerReceived = true;
}


void TriggerComponent::change(int64_t)
{
    m_triggerReceived = true;
}


void TriggerComponent::change(double)
{
    m_triggerReceived = true;
}


void TriggerComponent::change(const QString&)
{
    m_triggerReceived = true;
}


void TriggerComponent::loadState(const QVariantMap& state)
{
    auto triggered = state.find(QStringLiteral("triggered"));
    auto base = state.find(QStringLiteral("BaseComponent"));

    if (triggered != state.end())
    {
        m_triggerReceived = triggered->toBool();
    }
    if (base != state.end())
    {
        BaseComponent::loadState(base->toMap());
    }
}


QVariantMap TriggerComponent::storeState() const
{
    QVariantMap state;
    state.insert(QStringLiteral("triggered"), m_triggerReceived);
    state.insert(QStringLiteral("BaseComponent"), BaseComponent::storeState());
    return state;
}

