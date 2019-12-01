#include "sinewavecontroloperator.h"
#include <cmath>
#include "application.h"




BaseOperator * SineWaveControlOperator::create()
{
    return new SineWaveControlOperator();
}


const OperatorDescription SineWaveControlOperator::description
{
    "Sine Wave",
    "Control",
    &create,
    { },
    { },
    &ParameterPreview::Type
};


SineWaveControlOperator::SineWaveControlOperator()
    : BaseOperator(description)
{
    output.get_component(0)->setFlag(BaseComponent::IsEditable, false);
    output.get_component(0)->setFlag(BaseComponent::CanImport, false);
    input.get_component(0)->setFlag(BaseComponent::IsEditable, false);
    input.get_component(0)->setFlag(BaseComponent::IsVisible, false);
}


void SineWaveControlOperator::run()
{
    double val;

    if (input.get_component(0)->isImporting())
    {
        val = input.get();
    }
    else
    {
        val = application::clock()->get_elapsed_seconds();
    }

    output.set(amplitude.get() * std::sin(val / period.get()) + offset.get());
    update_view();
}
