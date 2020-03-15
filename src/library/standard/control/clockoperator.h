#pragma once

#include <chrono>

#include "model/BaseOperator.hpp"


class ClockOperator : public BaseOperator
{
public:

    ClockOperator(BaseZigZagObject* parent);

    void run() override;

    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorTypeDetails description;

private:

    std::chrono::system_clock clock;

    ButtonParameter reset_button{ this, "Reset" };
    IntParameter frames{ this, "Frames" };
    FloatParameter seconds{ this, "Seconds", 0 };
    FloatParameter minutes{ this, "Minutes", 0 };
    FloatParameter hours{ this, "Hours", 0 };
    IntParameter seconds_whole{ this, "Seconds Whole", 0 };
    IntParameter minutes_whole{ this, "Minutes Whole", 0 };
    IntParameter hours_whole{ this, "Hours Whole", 0 };

};
