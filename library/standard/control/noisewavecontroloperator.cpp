#include "noisewavecontroloperator.h"
#include "glm/gtc/noise.hpp"
#include "application.h"



BaseOperator * NoiseWaveControlOperator::create(BaseZigZagObject* parent)
{
    return new NoiseWaveControlOperator(parent);
}


const OperatorDescription NoiseWaveControlOperator::description
{
    "Noise Wave",
    "Control",
    &create,
    { },
    { },
    &ParameterView::Type
};



const EnumDefinition NoiseWaveControlOperator::NoiseType
{
    "NoiseType",
    {
        "Simplex Noise",
        "Perlin Noise"
    }
};



NoiseWaveControlOperator::NoiseWaveControlOperator(BaseZigZagObject* parent)
    : BaseOperator(parent, description)
{
    recalculate();
}



void NoiseWaveControlOperator::run()
{
    recalculate();
}

void NoiseWaveControlOperator::recalculate()
{
    glm::vec4 pos;

    if (use_time.getIndex() == 0)
    {
        pos = { application::clock()->get_elapsed_seconds() / slow_down.get(), 0, 0, 0 };
    }
    else
    {
        pos = { position.x(), position.y(), position.z(), position.w() };
    }

    if (noise_type.getIndex() == 0) // Simplex Noise
    {
        output.set(glm::simplex(pos) * amplitude.get() + offset.get());
    }
    else  // Perlin Noise
    {
        output.set(glm::perlin(pos) * amplitude.get() + offset.get());
    }
    update_view();
}
