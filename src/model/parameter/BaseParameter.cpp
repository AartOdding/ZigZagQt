#include "BaseParameter.hpp"
#include "BaseComponent.hpp"


BaseParameter::BaseParameter(ParameterType parameterType, BaseZigZagObject * parent, const QString& name)
    : BaseZigZagObject(parent, name),
      m_parameterType(parameterType)
{

}


/*
std::vector<BaseComponent*> BaseParameter::getComponents()
{
    return m_components;
}*/



QList<BaseComponent*> BaseParameter::getComponents() const
{
    return findChildren<BaseComponent*>(QString(), Qt::FindDirectChildrenOnly);
}



ParameterType BaseParameter::getParameterType() const
{
    return m_parameterType;
}



void BaseParameter::updateParameters()
{
    bool changed = false;

    for (auto component : getComponents())
    {
        changed |= component->update();
    }
    if (changed)
    {
        parameterChangedEvent(this);
    }
}
