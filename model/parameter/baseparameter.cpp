#include "baseparameter.h"
#include "parameterowner.h"
#include "application.h"
#include "model/baseoperator.h"

#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"



BaseParameter::BaseParameter(ParameterOwner* owner, ParameterType type, ParameterFamily family, const char * name)
    : m_owner(owner), m_name(name), m_type(type), m_family(family)
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


ParameterFamily BaseParameter::family() const
{
    return m_family;
}


const char * BaseParameter::name() const
{
    return m_name;
}


BaseOperator * BaseParameter::parent_operator() const
{
    Q_ASSERT(static_cast<BaseOperator*>(owner()->top_level_owner()));
    return static_cast<BaseOperator*>(owner()->top_level_owner());
}


bool BaseParameter::compatible_with(const BaseParameter* other) const
{
    return family() == other->family() && family() != ParameterFamily::DummyParameter;
}


void BaseParameter::flag_changed()
{
    m_changed = true;
    m_owner->flag_parameters_changed();

    for (auto e : m_exports)
    {
        e->import_flagged_changed();
    }
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


bool BaseParameter::is_exporting() const
{
    return !m_exports.empty();
}


BaseParameter * BaseParameter::get_import() const
{
    return m_import;
}


const std::vector<BaseParameter *>& BaseParameter::get_exports() const
{
    return m_exports;
}


// Undoable action
void BaseParameter::add_import(BaseParameter * exporting_import)
{
    auto model = application::project_model();
    auto undo_stack = model->get_undo_stack();
    undo_stack->push(new ConnectParametersCommand(exporting_import, this));
    import_flagged_changed();
}


// Undoable action
void BaseParameter::remove_import()
{
    if (m_import)
    {
        auto model = application::project_model();
        auto undo_stack = model->get_undo_stack();
        undo_stack->push(new DisconnectParametersCommand(m_import, this));
    }
}
