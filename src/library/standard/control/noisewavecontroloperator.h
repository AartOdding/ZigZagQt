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

    static const EnumDefinition NoiseType;

private:

    EnumDefinition UseTime { "Use Time as Position", { "True", "False" } };

    void recalculate();


    FloatParameter output   { this, "Output",    0 };
    EnumParameter noise_type { this, "Noise Type", NoiseType };
    EnumParameter use_time   { this, "Use time as Input", UseTime, 0 };
    FloatParameter amplitude{ this, "Amplitude", 1 };
    FloatParameter offset   { this, "Offset",    0 };
    Float4Parameter position{ this, "Position",  {} };
    FloatParameter slow_down{ this, "Slow Down X", 3 };

};
