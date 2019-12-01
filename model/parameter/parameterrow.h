#pragma once

#include "baseparameterold.h"

/*
class ParameterRow : public BaseParameter,
                     public ParameterOwner
{

public:

    ParameterRow(ParameterOwner* owner, const char * name)
        : BaseParameter(owner, ParameterType::ParameterRow, ParameterFamily::DummyParameter, name), ParameterOwner(owner)
    { }

    void flag_parameters_changed() override
    {
        ParameterOwner::flag_parameters_changed();
        BaseParameter::flag_changed();
    }


};
*/
