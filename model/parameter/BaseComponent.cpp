#include "BaseComponent.hpp"
#include "application.h"
#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"
#include "zigzaglib/xmlserializer.h"


#include <QXmlStreamReader>


BaseComponent::BaseComponent(BaseParameterOld * parameter_, ComponentType type_)
    : parameter(parameter_), m_componentType(type_)
{

}


BaseComponent::ComponentType BaseComponent::getComponentType() const
{
    return m_componentType;
}


BaseParameterOld * BaseComponent::getParameter() const
{
    return parameter;
}


int BaseComponent::getFlags() const
{
    return flags;
}


bool BaseComponent::hasFlag(ParameterFlags flag) const
{
    return (flags & flag) != 0;
}


bool BaseComponent::isImporting() const
{
    return import != nullptr;
}


bool BaseComponent::isExporting() const
{
    return !exports.empty();
}


BaseComponent * BaseComponent::getImport() const
{
    return import;
}


const std::vector<BaseComponent *>& BaseComponent::getExports() const
{
    return exports;
}


void BaseComponent::setFlags(ParameterFlags new_flags)
{
    if (flags != new_flags)
    {
        ParameterFlags old_flags = flags;
        flags = new_flags;
        emit flagsChanged(old_flags, new_flags);
    }
}


void BaseComponent::setFlag(ParameterFlags flag, bool value)
{
    auto current_value = hasFlag(flag);

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
        emit flagsChanged(old_flags, flags);
    }
}


void BaseComponent::setImport(BaseComponent * exporting_import)
{
    auto undo_stack = application::project_model()->get_undo_stack();
    undo_stack->push(new ConnectParametersCommand(exporting_import, this));
}


void BaseComponent::stopImporting()
{
    if (import)
    {
        auto undo_stack = application::project_model()->get_undo_stack();
        undo_stack->push(new DisconnectParametersCommand(import, this));
    }
}


void BaseComponent::stopExporting()
{
    while (!exports.empty())
    {
        exports.back()->stopImporting();
    }
}


void BaseComponent::readXml(QXmlStreamReader& xml)
{

}


void BaseComponent::writeXml(XmlSerializer& xml)
{
    xml.begin_element("BaseParameterComponent");
    xml.add_int_attribute("id", xml.id(this));

        xml.add_int_element("component_type", static_cast<qint32>(m_componentType));
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

















