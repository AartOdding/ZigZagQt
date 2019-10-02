#include "baseparametercomponent.h"
#include "application.h"
#include "model/xmlserializer.h"
#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"


#include <QXmlStreamReader>


BaseParameterComponent::BaseParameterComponent(BaseParameter * parameter_, ParameterComponentType type_)
    : parameter(parameter_), component_type(type_)
{

}


BaseParameterComponent::ParameterComponentType BaseParameterComponent::get_component_type() const
{
    return component_type;
}


BaseParameter * BaseParameterComponent::get_parameter() const
{
    return parameter;
}


int BaseParameterComponent::get_flags() const
{
    return flags;
}


bool BaseParameterComponent::has_flag(ParameterFlags flag) const
{
    return (flags & flag) != 0;
}


bool BaseParameterComponent::is_importing() const
{
    return import != nullptr;
}


bool BaseParameterComponent::is_exporting() const
{
    return !exports.empty();
}


BaseParameterComponent * BaseParameterComponent::get_import() const
{
    return import;
}


const std::vector<BaseParameterComponent *>& BaseParameterComponent::get_exports() const
{
    return exports;
}


void BaseParameterComponent::set_flags(ParameterFlags new_flags)
{
    if (flags != new_flags)
    {
        ParameterFlags old_flags = flags;
        flags = new_flags;
        emit flags_changed(old_flags, new_flags);
    }
}


void BaseParameterComponent::set_flag(ParameterFlags flag, bool value)
{
    auto current_value = has_flag(flag);

    if (current_value != value)
    {
        ParameterFlags old_flags = flags;

        if (value)
        {
            flags = static_cast<ParameterFlags>(flags | flag);
        }
        else
        {
            flags = static_cast<ParameterFlags>(flags & ~flag);
        }
        emit flags_changed(old_flags, flags);
    }
}


void BaseParameterComponent::set_import(BaseParameterComponent * exporting_import)
{
    auto undo_stack = application::project_model()->get_undo_stack();
    undo_stack->push(new ConnectParametersCommand(exporting_import, this));
}


void BaseParameterComponent::stop_importing()
{
    if (import)
    {
        auto undo_stack = application::project_model()->get_undo_stack();
        undo_stack->push(new DisconnectParametersCommand(import, this));
    }
}


void BaseParameterComponent::stop_exporting()
{
    while (!exports.empty())
    {
        exports.back()->stop_importing();
    }
}


void BaseParameterComponent::set_from_xml(QXmlStreamReader& xml)
{

}


void BaseParameterComponent::write_to_xml(XmlSerializer& xml)
{
    xml.begin_element("BaseParameterComponent");
    xml.add_int_attribute("id", xml.id(this));

        xml.add_int_element("component_type", static_cast<qint32>(component_type));
        xml.add_int_element("flags", static_cast<quint32>(flags));
        xml.add_int_element("import", xml.id(import));

        xml.begin_element("exports");
        xml.add_int_attribute("size", exports.size());

            for (auto e : exports)
            {
                xml.add_int_element("export", xml.id(e));
            }

        xml.end_element(); // ends exports

    xml.end_element(); // ends BaseParameterComponent
}

















