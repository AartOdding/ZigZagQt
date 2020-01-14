#pragma once

#include "BaseParameter.hpp"
#include "TriggerComponent.hpp"



class ButtonParameter : public BaseParameter
{
    Q_OBJECT

public:

    ButtonParameter(BaseZigZagObject * parent, const char * name);


private:

    TriggerComponent m_triggerComponent;

};
