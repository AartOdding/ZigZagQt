#pragma once

#include "model/BaseOperator.hpp"
#include "library/standard/control/parameterview.h"





class NoiseWaveControlOperator : public BaseOperator
{

public:

    NoiseWaveControlOperator(BaseZigZagObject* parent);

    void run() override;

    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorDescription description;

private:

    void recalculate();

    FloatParameter m_outputValue{ this, QStringLiteral("Output") };

    EnumParameter m_noiseType{ this, QStringLiteral("Noise Type"),
        {QStringLiteral("Simplex Noise"), QStringLiteral("Perlin Noise")}, 0 };

    EnumParameter m_timeIsInput{ this, QStringLiteral("Time is Input"),
        {QStringLiteral("True"), QStringLiteral("False")}, 0 };

    FloatParameter m_timeSpeed{ this, QStringLiteral("Time Speed"), 0.2 };

    FloatParameter m_amplitude{ this, QStringLiteral("Amplitude"), 1 };

    FloatParameter m_offset{ this, QStringLiteral("Offset"), 0 };

    Float4Parameter m_position{ this, QStringLiteral("Position"),  {} };

};
