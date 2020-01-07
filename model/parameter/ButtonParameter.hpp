#pragma once

#include "BaseParameter.hpp"
#include "TriggerComponent.hpp"



class ButtonPar : public BaseParameter
{
    Q_OBJECT

public:

    ButtonPar(BaseZigZagObject * parent, const char * name);


private:

    TriggerComponent m_triggerComponent;

};
