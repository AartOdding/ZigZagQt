#include "buttonparameter.h"

ButtonPar::ButtonPar(BaseParameterOld * parent, const char * name)
    : BaseParameterOld(parent, ParameterType::Button, name), pulse_component(this)
{

}
