#include "BaseParameter.hpp"
#include "BaseComponent.hpp"


BaseParameter::BaseParameter(ParameterType parameterType, BaseZigZagObject * parent, const QString& name)
    : BaseZigZagObject(parent, name), m_parameterType(parameterType)
{

}


std::vector<BaseComponent*> BaseParameter::getComponents()
{
    return m_components;
}


const std::vector<BaseComponent*>& BaseParameter::getComponents() const
{
    return m_components;
}


ParameterType BaseParameter::getParameterType() const
{
    return m_parameterType;
}


bool BaseParameter::update(bool silent)
{
    bool changed = false;

    for (auto component : m_components)
    {
        changed |= component->update();
    }
    for (auto parameter : getParameters())
    {
        changed |= parameter->update(false);
    }
    if (!silent && changed)
    {
        parameterChangeEvent(this);
    }
    return changed;
}


void BaseParameter::disconnectParameters(bool recursive)
{
    for (auto component : m_components)
    {
        component->stopImporting();
        component->stopExporting();
    }
    BaseZigZagObject::disconnectParameters(recursive);
}
