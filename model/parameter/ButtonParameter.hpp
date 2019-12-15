#pragma once

#include "BaseParameter.hpp"
#include "TriggerComponent.hpp"



class ButtonPar : public BaseParameter
{

public:

    ButtonPar(BaseZigZagObject * parent, const char * name);


private:

    TriggerComponent m_triggerComponent;

};
