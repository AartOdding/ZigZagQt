#include "noisewavecontroloperator.h"
#include "glm/gtc/noise.hpp"


EnumDefinition NoiseWaveControlOperator::NoiseType{ "NoiseType", { "Simplex Noise", "Perlin Noise" } };



NoiseWaveControlOperator::NoiseWaveControlOperator()
    : BaseOperator(Type)
{
    recalculate();
}



void NoiseWaveControlOperator::parameter_changed(BaseParameter*)
{
    recalculate();
}


void NoiseWaveControlOperator::run()
{

}

void NoiseWaveControlOperator::recalculate()
{
    glm::vec4 pos{ position.x(), position.y(), position.z(), position.w() };

    if (noise_type.get_index() == 0) // Simplex Noise
    {
        output.set(glm::simplex(pos) * amplitude.get() + offset.get());
    }
    else  // Perlin Noise
    {
        output.set(glm::perlin(pos));
    }
}
