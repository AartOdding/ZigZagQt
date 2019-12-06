#pragma once

#include "baseparameterold.h"
#include "TriggerComponent.hpp"



class ButtonPar : public BaseParameterOld
{

public:

    ButtonPar(BaseParameterOld * parent, const char * name);


    int num_components() const { return 1; }

    BaseComponent* get_component(int index) { return index == 0 ? &pulse_component : nullptr; }

    const BaseComponent* get_component(int index) const { return index == 0 ? &pulse_component : nullptr; }


private:

    TriggerComponent pulse_component;

};
