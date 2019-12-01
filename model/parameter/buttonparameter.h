#pragma once

#include "baseparameterold.h"
#include "pulseparametercomponent.h"



class ButtonPar : public BaseParameterOld
{

public:

    ButtonPar(BaseParameterOld * parent, const char * name);


    int num_components() const { return 1; }

    BaseComponent* get_component(int index) { return index == 0 ? &pulse_component : nullptr; }

    const BaseComponent* get_component(int index) const { return index == 0 ? &pulse_component : nullptr; }


private:

    PulseParameterComponent pulse_component;

};
