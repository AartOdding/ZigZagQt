#include "BaseComponent.hpp"
#include "BaseParameter.hpp"
#include "application.h"
#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"
#include "zigzaglib/xmlserializer.h"


#include <QXmlStreamReader>



BaseComponent::BaseComponent(BaseParameter * parameter)
    : m_parameter(parameter)
{
    for (ParameterFlags flag : defaultParameterFlags)
    {
        m_flags.set(static_cast<int>(flag), true);
    }
    m_parameter->m_components.push_back(this);
}


BaseComponent::~BaseComponent()
{
    auto pos = std::find(m_parameter->m_components.begin(), m_parameter->m_components.end(), this);

    if (pos != m_parameter->m_components.end())
    {
        m_parameter->m_components.erase(pos);
    }
}


bool BaseComponent::isImporting() const
{
    return m_import != nullptr;
}



bool BaseComponent::isExporting() const
{
    return !m_exports.empty();
}



void BaseComponent::startImporting(BaseComponent * exporting_import)
{
    auto undo_stack = application::project_model()->get_undo_stack();
    undo_stack->push(new ConnectParametersCommand(exporting_import, this));
}



void BaseComponent::stopImporting()
{
    if (m_import)
    {
        auto undo_stack = application::project_model()->get_undo_stack();
        undo_stack->push(new DisconnectParametersCommand(m_import, this));
    }
}



void BaseComponent::stopExporting()
{
    while (!m_exports.empty())
    {
        m_exports.back()->stopImporting();
    }
}



BaseComponent * BaseComponent::getImport() const
{
    return m_import;
}



const std::vector<BaseComponent *>& BaseComponent::getExports() const
{
    return m_exports;
}



bool BaseComponent::hasFlag(ParameterFlags flag) const
{
    return m_flags.test(static_cast<int>(flag));
}



void BaseComponent::setFlag(ParameterFlags flag, bool value)
{
    if (m_flags.test(static_cast<int>(flag)) != value)
    {
        m_flags.set(static_cast<int>(flag), value);
        emit flagChanged(flag, value);
    }
}



BaseParameter * BaseComponent::getParameter() const
{
    return m_parameter;
}



void BaseComponent::readXml(QXmlStreamReader& xml)
{

}



void BaseComponent::writeXml(XmlSerializer& xml)
{
    xml.begin_element("BaseParameterComponent");
    xml.add_int_attribute("id", xml.id(this));

        //xml.add_int_element("component_type", static_cast<qint32>(m_componentType));
        //xml.add_int_element("flags", static_cast<quint32>(m_flags));
        xml.add_int_element("import", xml.id(m_import));

        xml.begin_element("exports");
        xml.add_int_attribute("size", m_exports.size());

            for (auto e : m_exports)
            {
                xml.add_int_element("export", xml.id(e));
            }

        xml.end_element(); // ends exports

    xml.end_element(); // ends BaseParameterComponent
}
