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


    FloatPar output   { this, "Output",    0 };
    EnumParameter noise_type { this, "Noise Type", NoiseType };
    EnumParameter use_time   { this, "Use time as Input", UseTime, 0 };
    FloatPar amplitude{ this, "Amplitude", 1 };
    FloatPar offset   { this, "Offset",    0 };
    Float4Par position{ this, "Position",  {} };
    FloatPar slow_down{ this, "Slow Down X", 3 };

};
