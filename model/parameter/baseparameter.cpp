#include "baseparameter.h"
#include "application.h"
#include "parameterowner.h"

#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"



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


bool BaseParameter::is_importing() const
{
    return m_import != nullptr;
}


BaseParameter * BaseParameter::get_import() const
{
    return m_import;
}


const std::vector<BaseParameter *> BaseParameter::get_exports() const
{
    return m_exports;
}


// Undoable action
void BaseParameter::add_import(BaseParameter * import)
{
    auto model = application::project_model();
    auto undo_stack = model->get_undo_stack();
    undo_stack->push(new ConnectParametersCommand(import, this));
}


// Undoable action
void BaseParameter::remove_import()
{
    auto model = application::project_model();
    auto undo_stack = model->get_undo_stack();
    undo_stack->push(new DisconnectParametersCommand(m_import, this));
}
