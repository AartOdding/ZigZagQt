#pragma once

#include "model/baseoperator.h"
#include "library/standard/control/parameterpreview.h"



class IncreasingValueOperator : public BaseOperator
{

public:

    IncreasingValueOperator();

    void run() override;

    static BaseOperator * create();

    static const OperatorDescription description;

protected:

    void parameterChangeEvent(const BaseParameter * parameter) override;


private:

    void recalculate();

    FloatPar value  { this, "Value", 0 };
    ButtonPar reset { this, "Reset"    };
    FloatPar speed  { this, "Speed", 0 };

    float last_frame_time = 0;

};
