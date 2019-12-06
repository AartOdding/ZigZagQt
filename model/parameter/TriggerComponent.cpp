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



void TriggerComponent::change(int64_t)
{
    m_triggerReceived = true;
}



void TriggerComponent::change(double)
{
    m_triggerReceived = true;
}
