#include "sinewavecontroloperator.h"
#include <cmath>
#include "application.h"



SineWaveControlOperator::SineWaveControlOperator()
    : BaseOperator(Type)
{
    output.get_component(0)->set_flag(BaseParameterComponent::IsEditable, false);
    output.get_component(0)->set_flag(BaseParameterComponent::CanImport, false);
    input.get_component(0)->set_flag(BaseParameterComponent::IsEditable, false);
    input.get_component(0)->set_flag(BaseParameterComponent::IsVisible, false);
}


void SineWaveControlOperator::run()
{
    double val;

    if (input.get_component(0)->is_importing())
    {
        val = input.get();
    }
    else
    {
        val = application::clock()->get_elapsed_seconds();
    }

    output.set(amplitude.get() * std::sin(val / period.get()) + offset.get());
}
