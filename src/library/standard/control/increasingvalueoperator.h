#pragma once

#include "model/BaseOperator.hpp"
#include "library/standard/control/parameterview.h"



class IncreasingValueOperator : public BaseOperator
{

public:

    IncreasingValueOperator(BaseZigZagObject* parent);

    void run() override;

    static BaseOperator * create(BaseZigZagObject* parent);

    static const OperatorTypeDetails description;

protected:

    void parameterChangeEvent(const BaseParameter * parameter) override;


private:

    void recalculate();

    FloatParameter value  { this, "Value", 0 };
    ButtonParameter reset { this, "Reset"    };
    FloatParameter speed  { this, "Speed", 0 };

    float last_frame_time = 0;

};
