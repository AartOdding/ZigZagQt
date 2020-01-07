#include "BaseComponent.hpp"
#include "BaseParameter.hpp"
#include "model/BaseZigZagObject.hpp"
#include "application.h"
#include "model/projectmodel.h"
#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"
#include "zigzaglib/xmlserializer.h"


#include <QXmlStreamReader>



BaseComponent::BaseComponent(BaseParameter * parameter)
    : QObject(parameter),
      m_parameter(parameter)
{
    for (ParameterFlags flag : defaultParameterFlags)
    {
        m_flags.set(static_cast<int>(flag), true);
    }
}



BaseComponent::~BaseComponent()
{
}



QString BaseComponent::uniqueName() const
{
    const QObject* object = this;
    auto thisName = objectName();

    std::vector<QString> parentNames;
    parentNames.reserve(6);
    int size = thisName.length();

    // While there is a parent that is a BaseZigZagObject.
    while (qobject_cast<const BaseZigZagObject*>(object->parent()))
    {
        object = static_cast<const BaseZigZagObject*>(object->parent());
        parentNames.push_back(object->objectName());
        size += parentNames.back().length() + 1; // +1 for the points
    }

    QString result;
    result.reserve(size);

    // Reverse iterate parents: start at root towards this.
    for (auto it = parentNames.rbegin(); it != parentNames.rend(); ++it)
    {
        result.append(*it).append('.');
    }
    return result.append(thisName);
}



bool BaseComponent::isImporting() const
{
    return m_import != nullptr;
}



bool BaseComponent::isExporting() const
{
    return !m_exports.empty();
}



bool BaseComponent::isImportingFrom(BaseComponent * exporter) const
{
    return m_import == exporter;
}



bool BaseComponent::isExportingTo(BaseComponent * importer) const
{
    return std::find(m_exports.begin(), m_exports.end(), importer) != m_exports.end();
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



void BaseComponent::loadState(const QVariantMap& map)
{
    auto flags = map.find(QStringLiteral("flags"));
    auto import = map.find(QStringLiteral("import"));
    auto exports = map.find(QStringLiteral("exports"));

    if (flags != map.end())
    {
        m_flags = flags->value<quint64>();
    }
    if (import != map.end())
    {
        m_import = qobject_cast<BaseComponent*>(m_parameter->findObject(import->toString()));
    }
    if (exports != map.end())
    {
        auto exportsList = exports->toStringList();

        for (auto& e : exportsList)
        {
            auto ptr = qobject_cast<BaseComponent*>(m_parameter->findObject(e));
            if (ptr)
            {
                m_exports.push_back(ptr);
            }
        }
    }

}



QVariantMap BaseComponent::storeState() const
{
    QVariantMap state;

    state.insert(QStringLiteral("flags"), m_flags.to_ullong());

    if (m_import)
    {
        state.insert(QStringLiteral("import"), m_import->uniqueName());
    }

    if (m_exports.size() > 0)
    {
        QStringList exports;
        exports.reserve(m_exports.size());

        for (auto& e : m_exports)
        {
            exports << e->uniqueName();
        }

        state.insert(QStringLiteral("exports"), exports);
    }
    return state;
}

/*
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
}*/
