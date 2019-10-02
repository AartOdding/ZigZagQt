#include "pulseparametercomponent.h"



PulseParameterComponent::PulseParameterComponent(BaseParameter* parameter)
    : BaseParameterComponent(parameter, BaseParameterComponent::Int64)
{

}


bool PulseParameterComponent::process_changes()
{
    if (received_signal)
    {
        received_signal = false;
        return true;
    }
    return false;
}


void PulseParameterComponent::set_later(int64_t)
{
    received_signal = true;
}


void PulseParameterComponent::set_later(double)
{
    received_signal = true;
}
