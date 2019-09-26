#include "parametercomponentsignal.h"



ParameterComponentSignal::ParameterComponentSignal(BaseParameter* parameter)
    : ParameterComponent(parameter, ParameterComponent::Int64)
{

}


bool ParameterComponentSignal::process_changes()
{
    if (received_signal)
    {
        received_signal = false;
        return true;
    }
    return false;
}


void ParameterComponentSignal::set_later(int64_t)
{
    received_signal = true;
}


void ParameterComponentSignal::set_later(double)
{
    received_signal = true;
}
