#pragma once

#include <chrono>

#include "model/baseoperator.h"


class SystemClockOperator : public BaseOperator
{
public:

    SystemClockOperator();

    void run() override;

    static BaseOperator * create() { return new SystemClockOperator(); }

    static const inline OperatorTypeInfo Type { "Clock", "Standard/Control", { }, { }, false, &create };

private:

    std::chrono::system_clock clock;

    DoublePar seconds{ this, "Seconds", 0 };
    IntPar frame{ this, "Frame" };

};
