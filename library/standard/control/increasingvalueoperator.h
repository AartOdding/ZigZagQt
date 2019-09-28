#pragma once

#include "model/baseoperator.h"



class IncreasingValueOperator : public BaseOperator
{

public:

    IncreasingValueOperator();

    void run() override;

    void parameter_changed(BaseParameter * parameter) override;


    static BaseOperator * create() { return new IncreasingValueOperator(); }

    static const inline OperatorTypeInfo Type { "Increasing Value", "Control", { }, { }, nullptr, &create };

private:

    void recalculate();

    DoublePar value   { this, "Value", 0 };
    ButtonPar reset    { this, "Reset"    };
    DoublePar speed    { this, "Speed", 0 };

    float last_frame_time = 0;

};
