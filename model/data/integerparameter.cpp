#include "integerparameter.h"


IntegerParameter::IntegerParameter(ParameterMode mode)
    : BaseParameter("integer", mode)
{ }


IntegerParameter::IntegerParameter(int initial_value, ParameterMode mode)
    : BaseParameter("integer", mode)
{
    set(initial_value);
}


void IntegerParameter::set(int new_value)
{
    if (value != new_value)
    {
        value = new_value;
        propagate_changes();
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
