#include "pulseparametercomponent.h"



PulseParameterComponent::PulseParameterComponent(BaseParameterOld* parameter)
    : BaseComponent(parameter, BaseComponent::Int64)
{

}


bool PulseParameterComponent::run()
{
    if (received_signal)
    {
        received_signal = false;
        return true;
    }
    return false;
}


void PulseParameterComponent::change(int64_t)
{
    received_signal = true;
}


void PulseParameterComponent::change(double)
{
    received_signal = true;
}
