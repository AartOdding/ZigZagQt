#pragma once

#include "model/parameter/baseparameter.h"



class IntegerParameter : public BaseParameter
{
    Q_OBJECT

public:

    IntegerParameter(const char * name, ParameterMode mode = ParameterMode::PASSTHROUGH);

    IntegerParameter(const char * name, int initial_value, ParameterMode mode = ParameterMode::PASSTHROUGH);


    int get() const;

    void operator=(int new_value);

    operator int() const;


public slots:

    void set(int new_value);


private:

    int value = 0;


};
