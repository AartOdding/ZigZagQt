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

    FloatParameter output   { this, "Output",    0 };
    FloatParameter input    { this, "Input",     0 };
    FloatParameter amplitude{ this, "Amplitude", 1 };
    FloatParameter offset   { this, "Offset",    0 };
    FloatParameter period   { this, "Period",    5, 0, INT_MAX };

};
