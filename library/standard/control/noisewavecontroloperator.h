#pragma once

#include "model/baseoperator.h"





class NoiseWaveControlOperator : public BaseOperator
{

public:

    NoiseWaveControlOperator();

    void run() override;

    void parameter_changed(BaseParameter*) override;

    static BaseOperator * create() { return new NoiseWaveControlOperator(); }

    static const inline OperatorTypeInfo Type { "Noise Wave", "Control", { }, { }, nullptr, &create };

private:

    void recalculate();

    static EnumDefinition NoiseType;

    DoublePar output   { this, "Output",    0 };
    EnumPar noise_type { this, "Noise Type", NoiseType };
    DoublePar amplitude{ this, "Amplitude", 1 };
    DoublePar offset   { this, "Offset",    0 };
    Double4Par position{ this, "Position",  {} };

};
