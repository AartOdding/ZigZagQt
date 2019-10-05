#include "buttonparameter.h"

ButtonPar::ButtonPar(BaseParameter * parent, const char * name)
    : BaseParameter(parent, ParameterType::Button, name), pulse_component(this)
{

}
