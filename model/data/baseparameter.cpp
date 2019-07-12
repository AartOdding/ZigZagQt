#include "baseparameter.h"


BaseParameter::BaseParameter(const char * parameter_name, ParameterMode mode_)
    : name(parameter_name), mode(mode_)
{

}


ParameterMode BaseParameter::get_mode() const
{
    return mode;
}

