#include "parametercomponent.h"
#include "application.h"
#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"



ParameterComponent::ParameterComponent(BaseParameter * parameter_, ParameterComponentType type_)
    : parameter(parameter_), type(type_)
{

}


ParameterComponent::ParameterComponentType ParameterComponent::get_type() const
{
    return type;
}


BaseParameter * ParameterComponent::get_parameter() const
{
    return parameter;
}


bool ParameterComponent::is_importing() const
{
    return import != nullptr;
}


bool ParameterComponent::is_exporting() const
{
    return !exports.empty();
}


ParameterComponent * ParameterComponent::get_import() const
{
    return import;
}


const std::vector<ParameterComponent *>& ParameterComponent::get_exports() const
{
    return exports;
}


void ParameterComponent::set_import(ParameterComponent * exporting_import)
{
    auto undo_stack = application::project_model()->get_undo_stack();
    undo_stack->push(new ConnectParametersCommand(exporting_import, this));
}


void ParameterComponent::stop_importing()
{
    if (import)
    {
        auto undo_stack = application::project_model()->get_undo_stack();
        undo_stack->push(new DisconnectParametersCommand(import, this));
    }
}


void ParameterComponent::stop_exporting()
{
    while (!exports.empty())
    {
        exports.back()->stop_importing();
    }
}
