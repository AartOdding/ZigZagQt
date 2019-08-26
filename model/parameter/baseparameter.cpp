#include "baseparameter.h"

#include "model/parameter/parameterowner.h"


namespace parameter
{

    BaseParameter::BaseParameter(ParameterOwner* owner_, ParameterType type_, const char * name_)
        : owner(owner_), type(type_), name(name_)
    {
        Q_ASSERT(owner);
        owner->register_parameter(this);
    }


    parameter::UpdateMode BaseParameter::update_mode() const
    {
        return m_update_mode;
    }


    void BaseParameter::set_update_mode(const UpdateMode& mode)
    {
        m_update_mode = mode;
    }



}
