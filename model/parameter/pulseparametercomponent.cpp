#include "pulseparametercomponent.h"



PulseParameterComponent::PulseParameterComponent(BaseParameterOld* parameter)
    : BaseComponent(parameter, BaseComponent::Int64)
{

}


bool PulseParameterComponent::update()
{
    if (received_signal)
    {
        received_signal = false;
        return true;
    }
    return false;
}


void PulseParameterComponent::store(int64_t)
{
    received_signal = true;
}


void PulseParameterComponent::store(double)
{
    received_signal = true;
}
