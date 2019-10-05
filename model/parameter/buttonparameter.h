#pragma once

#include "baseparameter.h"
#include "pulseparametercomponent.h"



class ButtonPar : public BaseParameter
{

public:

    ButtonPar(BaseParameter * parent, const char * name);


    int num_components() const { return 1; }

    BaseParameterComponent* get_component(int index) { return index == 0 ? &pulse_component : nullptr; }

    const BaseParameterComponent* get_component(int index) const { return index == 0 ? &pulse_component : nullptr; }


private:

    PulseParameterComponent pulse_component;

};
