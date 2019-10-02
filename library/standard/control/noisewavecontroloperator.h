#pragma once

#include "model/baseoperator.h"





class NoiseWaveControlOperator : public BaseOperator
{

public:

    NoiseWaveControlOperator();

    void run() override;

    static BaseOperator * create() { return new NoiseWaveControlOperator(); }

    static const inline OperatorTypeInfo Type { "Noise Wave", "Control", { }, { }, nullptr, &create };

private:

    EnumDefinition UseTime { "Use Time as Position", { "True", "False" } };

    void recalculate();

    static EnumDefinition NoiseType;

    FloatPar output   { this, "Output",    0 };
    EnumPar noise_type { this, "Noise Type", NoiseType };
    EnumPar use_time   { this, "Use time as Input", UseTime, 0 };
    FloatPar amplitude{ this, "Amplitude", 1 };
    FloatPar offset   { this, "Offset",    0 };
    Float4Par position{ this, "Position",  {} };
    FloatPar slow_down{ this, "Slow Down X", 3 };

};
