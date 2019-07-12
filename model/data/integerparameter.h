#pragma once

#include "model/data/baseparameter.h"



class IntegerParameter : public BaseParameter
{

public:

    IntegerParameter(ParameterMode mode_ = ParameterMode::PASSTHROUGH);

    IntegerParameter(int initial_value, ParameterMode mode_ = ParameterMode::PASSTHROUGH);

    void set(int new_value);

    int get() const;

    void operator=(int new_value);

    operator int() const;

private:

    int value = 0;


};
