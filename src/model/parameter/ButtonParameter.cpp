#include "ButtonParameter.hpp"



ButtonParameter::ButtonParameter(BaseZigZagObject * parent, const char * name)
    : BaseParameter(ParameterType::Button, parent, name),
      m_triggerComponent(this, name)
{

}
