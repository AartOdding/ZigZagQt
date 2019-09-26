#pragma once

#include "baseparameter.h"
#include "parametercomponentsignal.h"



class ButtonPar : public BaseParameter
{

public:

    ButtonPar(ParameterOwner * owner, const char * name);


    int num_components() const { return 1; }

    ParameterComponent* get_component(int index) { return index == 0 ? &signal_component : nullptr; }

    const ParameterComponent* get_component(int index) const { return index == 0 ? &signal_component : nullptr; }


private:

    ParameterComponentSignal signal_component;

};
