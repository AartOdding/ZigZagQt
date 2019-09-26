#pragma once

#include "model/baseoperator.h"



class SineWaveControlOperator : public BaseOperator
{

public:

    SineWaveControlOperator();

    void run() override;

    static BaseOperator * create() { return new SineWaveControlOperator(); }

    static const inline OperatorTypeInfo Type { "Sine Wave", "Control", { }, { }, nullptr, &create };

private:

    DoublePar output   { this, "Output",    0 };
    DoublePar input    { this, "Input",     0 };
    DoublePar amplitude{ this, "Amplitude", 1 };
    DoublePar offset   { this, "Offset",    0 };
    DoublePar period   { this, "Period",    5, 0, INT_MAX };

};
