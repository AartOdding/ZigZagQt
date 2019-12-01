#pragma once

#include "model/baseoperator.h"
#include "library/standard/control/parameterpreview.h"



class IncreasingValueOperator : public BaseOperator
{

public:

    IncreasingValueOperator();

    void run() override;

    void parameter_changed(BaseParameterOld * parameter) override;


    static BaseOperator * create();

    static const OperatorDescription description;

private:

    void recalculate();

    FloatPar value  { this, "Value", 0 };
    ButtonPar reset { this, "Reset"    };
    FloatPar speed  { this, "Speed", 0 };

    float last_frame_time = 0;

};
