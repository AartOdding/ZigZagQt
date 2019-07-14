#include "baseparameter.h"


BaseParameter::BaseParameter(const char * parameter_type, ParameterMode mode_)
    : type_name(parameter_type), mode(mode_)
{

}


ParameterMode BaseParameter::get_mode() const
{
    return mode;
}

