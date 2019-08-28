#pragma once

#include "baseparameter.h"
#include "parameterowner.h"


class ParameterRow : public BaseParameter,
                     public ParameterOwner
{

public:

    ParameterRow(ParameterOwner* owner, const char * name)
        : BaseParameter(owner, ParameterType::ParameterRow, name), ParameterOwner(owner)
    { }

    void flag_parameters_changed() override
    {
        ParameterOwner::flag_parameters_changed();
        BaseParameter::flag_changed();
    }


};
