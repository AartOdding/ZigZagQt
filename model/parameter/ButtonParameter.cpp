#include "ButtonParameter.hpp"



ButtonPar::ButtonPar(BaseZigZagObject * parent, const char * name)
    : BaseParameter(ParameterType::Button, parent, name),
      m_triggerComponent(this)
{

}
