#pragma once

#include "model/data/baseparameter.h"



class IntegerParameter : public BaseParameter
{

public:

    IntegerParameter() = default;

    IntegerParameter(int initial_value, ParameterMode mode_ = ParameterMode::PASSTHROUGH)
        : BaseParameter(mode_)
    {
        set(initial_value);
    }

    void set(int new_value)
    {
        if (value != new_value)
        {
            value = new_value;
            apply_change();
        }
    }

    int get() const
    {
        return value;
    }

    void operator=(int new_value)
    {
        set(new_value);
    }

    operator int() const
    {
        return value;
    }

private:

    int value = 0;


};
