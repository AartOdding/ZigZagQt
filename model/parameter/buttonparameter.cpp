#include "buttonparameter.h"

ButtonPar::ButtonPar(ParameterOwner * owner, const char * name)
    : BaseParameter(owner, ParameterType::Button, name), signal_component(this)
{

}
