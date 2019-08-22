#include "integerparameter.h"

#include <iostream>

IntegerParameter::IntegerParameter(ParameterOwner * owner, const char * name, int value_)
    : BaseParameter(owner, ParameterType::Int, name)
{
    value = value_;
}


void IntegerParameter::set(int new_value)
{
    std::cout << "set\n";
    if (value != new_value)
    {
        value = new_value;
        emit_changes();
    }
}


int IntegerParameter::get() const
{
    return value;
}


void IntegerParameter::operator=(int new_value)
{
    set(new_value);
}


IntegerParameter::operator int() const
{
    return value;
}
