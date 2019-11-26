#pragma once

#include "model/baseoperator.h"
#include "library/standard/control/ParameterPreview.hpp"



class SineWaveControlOperator : public BaseOperator
{

public:

    SineWaveControlOperator();

    void run() override;

    static BaseOperator * create() { return new SineWaveControlOperator(); }

    static const inline OperatorTypeInfo Type { "Sine Wave", "Control", { }, { }, &ParameterPreview::Type , &create };

private:

    FloatPar output   { this, "Output",    0 };
    FloatPar input    { this, "Input",     0 };
    FloatPar amplitude{ this, "Amplitude", 1 };
    FloatPar offset   { this, "Offset",    0 };
    FloatPar period   { this, "Period",    5, 0, INT_MAX };

};
