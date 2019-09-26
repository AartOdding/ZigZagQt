#include "sinewavecontroloperator.h"
#include <cmath>
#include "application.h"



SineWaveControlOperator::SineWaveControlOperator()
    : BaseOperator(Type)
{
    output.get_component(0)->set_flag(ParameterComponent::IsEditable, false);
    output.get_component(0)->set_flag(ParameterComponent::CanImport, false);
    input.get_component(0)->set_flag(ParameterComponent::IsEditable, false);
    input.get_component(0)->set_flag(ParameterComponent::IsVisible, false);
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
