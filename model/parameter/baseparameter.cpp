#include "baseparameter.h"


BaseParameter::BaseParameter(ParameterType p_type, const char * p_name, ParameterMode p_mode)
    : name(p_name), type(p_type), mode(p_mode)
{

}

