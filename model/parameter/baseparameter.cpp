#include "baseparameter.h"
#include "parameterowner.h"
#include "application.h"
#include "model/baseoperator.h"

#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"



BaseParameter::BaseParameter(ParameterOwner* parent_, ParameterType type_, const QString& name_)
    : name(name_), parent(parent_), parameter_type(type_)
{
    // BaseOperator also inherits parameter so parent can be nullptr.
    if (parent)
    {
        parent->register_parameter(this);
    }
}


BaseParameter::~BaseParameter()
{
    if (parent)
    {
        parent->deregister_parameter(this);
    }
}


void BaseParameter::remove_imports_exports()
{
    for (int i = 0; i < num_components(); ++i)
    {
        get_component(i)->stop_importing();
        get_component(i)->stop_exporting();
    }
}


void BaseParameter::process_parameter_changes()
{
    bool changed = false;
    for (int i = 0; i < num_components(); ++i)
    {
        changed |= get_component(i)->process_changes();
    }
    if (changed)
    {
        ParameterOwner * owner = get_parent();

        while(owner)
        {
            owner->parameter_changed(this);
            owner = owner->get_parent();
        }
    }
}


const QString& BaseParameter::get_name() const
{
    return name;
}


ParameterType BaseParameter::get_parameter_type() const
{
    return parameter_type;
}


ParameterOwner * BaseParameter::get_parent() const
{
    return parent;
}


BaseOperator * BaseParameter::get_operator() const
{
    if (parent->is_operator())
    {
        return static_cast<BaseOperator*>(parent);
    }
    else
    {
        return parent->get_operator();
    }
}
