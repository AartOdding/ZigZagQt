#include "sinewavecontroloperator.h"
#include <cmath>
#include "app.h"




BaseOperator * SineWaveControlOperator::create(BaseZigZagObject* parent)
{
    return new SineWaveControlOperator(parent);
}


const OperatorTypeDetails SineWaveControlOperator::description
{
    "Sine Wave",
    "Control",
};


SineWaveControlOperator::SineWaveControlOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, description)
{
    output.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
    output.getComponents()[0]->setFlag(ParameterFlag::CanImport, false);
    input.getComponents()[0]->setFlag(ParameterFlag::IsEditable, false);
    input.getComponents()[0]->setFlag(ParameterFlag::IsVisible, false);
}


void SineWaveControlOperator::run()
{
    double val;

    if (input.getComponents()[0]->isImporting())
    {
        val = input.get();
    }
    else
    {
        //val = application::clock()->get_elapsed_seconds();
    }

    output.set(amplitude.get() * std::sin(val / period.get()) + offset.get());
    updateView();
}
