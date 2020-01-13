#pragma once

#include <chrono>

#include "model/BaseOperator.hpp"


class ClockOperator : public BaseOperator
{
public:

    ClockOperator(BaseZigZagObject* parent);

    void run() override;

    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorDescription description;

private:

    std::chrono::system_clock clock;

    ButtonPar reset_button{ this, "Reset" };
    IntPar frames{ this, "Frames" };
    FloatPar seconds{ this, "Seconds", 0 };
    FloatPar minutes{ this, "Minutes", 0 };
    FloatPar hours{ this, "Hours", 0 };
    IntPar seconds_whole{ this, "Seconds Whole", 0 };
    IntPar minutes_whole{ this, "Minutes Whole", 0 };
    IntPar hours_whole{ this, "Hours Whole", 0 };

};
