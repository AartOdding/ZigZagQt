#pragma once

#include "model/BaseOperator.hpp"
#include "library/standard/control/parameterview.h"



class SineWaveControlOperator : public BaseOperator
{

public:

    SineWaveControlOperator(BaseZigZagObject* parent);

    void run() override;

    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorDescription description;

private:

    FloatPar output   { this, "Output",    0 };
    FloatPar input    { this, "Input",     0 };
    FloatPar amplitude{ this, "Amplitude", 1 };
    FloatPar offset   { this, "Offset",    0 };
    FloatPar period   { this, "Period",    5, 0, INT_MAX };

};
