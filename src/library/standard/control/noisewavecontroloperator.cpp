#include "noisewavecontroloperator.h"
#include "glm/gtc/noise.hpp"
#include "app.h"



BaseOperator * NoiseWaveControlOperator::create(BaseZigZagObject* parent)
{
    return new NoiseWaveControlOperator(parent);
}


const OperatorTypeDetails NoiseWaveControlOperator::description
{
    "Noise Wave",
    "Control"
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

    if (m_timeIsInput.getIndex() == 0)
    {
        //pos = { application::clock()->get_elapsed_seconds() * m_timeSpeed.get(), 0, 0, 0 };
    }
    else
    {
        pos = { m_position.x(), m_position.y(), m_position.z(), m_position.w() };
    }

    if (m_noiseType.getIndex() == 0) // Simplex Noise
    {
        m_outputValue.set(glm::simplex(pos) * m_amplitude.get() + m_offset.get());
    }
    else  // Perlin Noise
    {
        m_outputValue.set(glm::perlin(pos) * m_amplitude.get() + m_offset.get());
    }
    updateView();
}
