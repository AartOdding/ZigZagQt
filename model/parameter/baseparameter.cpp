#include "baseparameter.h"
#include "parameterowner.h"



BaseParameter::BaseParameter(ParameterOwner& owner, ParameterType type, const char * name)
    : BaseParameter(&owner, type, name)
{ }


BaseParameter::BaseParameter(ParameterOwner* owner, ParameterType type, const char * name)
    : m_owner(owner), m_type(type), m_name(name)
{
    Q_ASSERT(owner);
    owner->register_parameter(this);
}


BaseParameter::~BaseParameter()
{
    m_owner->deregister_parameter(this);
}


ParameterOwner * BaseParameter::owner() const
{
    return m_owner;
}


ParameterType BaseParameter::type() const
{
    return m_type;
}


const char * BaseParameter::name() const
{
    return m_name;
}


bool BaseParameter::minimal_updates() const
{
    return m_minimal_updates;
}


void BaseParameter::set_minimal_updates(bool value)
{
    m_minimal_updates = value;
}


bool BaseParameter::rollover() const
{
    return m_rollover;
}


void BaseParameter::set_rollover(bool value)
{
    m_rollover = value;
}


void BaseParameter::flag_changed()
{
    m_changed = true;
    m_owner->flag_parameters_changed();
}


void BaseParameter::reset_changed_flag()
{
    m_changed = false;
}


bool BaseParameter::has_changed() const
{
    return m_changed;
}
