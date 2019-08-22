#pragma once

#include "model/parameter/baseparameter.h"



class IntegerParameter : public BaseParameter
{
    Q_OBJECT

public:

    IntegerParameter(ParameterOwner * owner, const char * name, int value = 0);


    int get() const;

    void operator=(int new_value);

    operator int() const;


public slots:

    void set(int new_value);


private:

    int value = 0;


};
