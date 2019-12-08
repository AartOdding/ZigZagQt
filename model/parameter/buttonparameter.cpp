#include "buttonparameter.h"

ButtonPar::ButtonPar(BaseZigZagObject * parent, const char * name)
    : BaseParameter(ParameterType::Button, parent, name), pulse_component(this)
{

}
