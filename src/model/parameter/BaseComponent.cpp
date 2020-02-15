#include "BaseComponent.hpp"
#include "BaseParameter.hpp"
#include "model/BaseZigZagObject.hpp"
#include "application.h"
#include "model/OperatorNetwork.hpp"
#include "command/connectparameterscommand.h"
#include "command/disconnectparameterscommand.h"


#include <QXmlStreamReader>




BaseComponent::BaseComponent(BaseParameter * parentParameter, const QString& name)
    : BaseZigZagObject(parentParameter, name),
      m_parameter(parentParameter)
{
}



BaseComponent::~BaseComponent()
{
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
    auto undo_stack = application::project_model()->getUndoStack();
    undo_stack->push(new ConnectParametersCommand(exporting_import, this));
}



void BaseComponent::stopImporting()
{
    if (m_import)
    {
        auto undo_stack = application::project_model()->getUndoStack();
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



ParameterFlags BaseComponent::getFlags() const
{
    return m_flags;
}



bool BaseComponent::getFlag(ParameterFlag flag) const
{
    return m_flags.getFlag(flag);
}



void BaseComponent::setFlag(ParameterFlag flag, bool value)
{
    if (m_flags.getFlag(flag) != value)
    {
        m_flags.setFlag(flag, value);
        emit flagsChanged(m_flags);
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
        m_flags = flags->value<quint32>();
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

    state.insert(QStringLiteral("flags"), static_cast<quint32>(m_flags));

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



void BaseComponent::disconnectParameters()
{
    stopImporting();
    stopExporting();
}
