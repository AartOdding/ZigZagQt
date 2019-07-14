#pragma once

#include "model/parameter/baseparameter.h"



class IntegerParameter : public BaseParameter
{

public:

    IntegerParameter(ParameterMode mode = ParameterMode::PASSTHROUGH);

    IntegerParameter(int initial_value, ParameterMode mode = ParameterMode::PASSTHROUGH);

    void set(int new_value);

    int get() const;

    void operator=(int new_value);

    operator int() const;

private:

    int value = 0;


};
