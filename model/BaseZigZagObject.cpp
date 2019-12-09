#include "BaseZigZagObject.hpp"

#include "model/parameter/BaseParameter.hpp"



BaseZigZagObject::BaseZigZagObject(BaseZigZagObject * parent, const QString& name, bool isParameter)
    : m_parent(parent), m_name(name)
{
    if (isParameter)
    {
        if (m_parent)
        {
            m_parent->m_parameters.push_back(static_cast<BaseParameter*>(this));
        }
    }
    else
    {
        if (m_parent)
        {
            m_parent->m_children.push_back(this);
        }
    }
}


BaseZigZagObject::~BaseZigZagObject()
{
    if (m_parent)
    {
        BaseParameter* parameter = dynamic_cast<BaseParameter*>(this);

        if (parameter)
        {
            auto pos = std::find(m_parent->m_parameters.begin(), m_parent->m_parameters.end(), parameter);
            if (pos != m_parent->m_parameters.end()) m_parent->m_parameters.erase(pos);
        }
        else
        {
            auto pos = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);
            if (pos != m_parent->m_children.end()) m_parent->m_children.erase(pos);
        }
    }
}


BaseZigZagObject * BaseZigZagObject::getParent()
{
    return m_parent;
}


const BaseZigZagObject * BaseZigZagObject::getParent() const
{
    return m_parent;
}


BaseZigZagObject * BaseZigZagObject::getTopParent()
{
    BaseZigZagObject * topParent = this;

    while (topParent->m_parent)
    {
        topParent = m_parent;
    }
    return topParent;
}


const BaseZigZagObject * BaseZigZagObject::getTopParent() const
{
    const BaseZigZagObject * topParent = this;

    while (topParent->m_parent)
    {
        topParent = m_parent;
    }
    return topParent;
}


std::vector<BaseZigZagObject*> BaseZigZagObject::getChildren()
{
    return m_children;
}


const std::vector<BaseZigZagObject*>& BaseZigZagObject::getChildren() const
{
    return m_children;
}


std::vector<BaseParameter*> BaseZigZagObject::getParameters()
{
    return m_parameters;
}


const std::vector<BaseParameter*>& BaseZigZagObject::getParameters() const
{
    return m_parameters;
}


void BaseZigZagObject::updateParameters(bool recursive)
{
    for (auto par : m_parameters)
    {
        par->update();
    }
    if (recursive)
    {
        for (auto child : m_children)
        {
            child->updateParameters();
        }
    }
}


void BaseZigZagObject::disconnectParameters(bool recursive)
{
    for (auto par : m_parameters)
    {
        par->disconnectParameters(recursive);
    }
    if (recursive)
    {
        for (auto child : m_children)
        {
            child->disconnectParameters(recursive);
        }
    }
}


void BaseZigZagObject::parameterChangeEvent(const BaseParameter* parameter)
{
    if (m_parent)
    {
        m_parent->parameterChangeEvent(parameter);
    }
}

const QString& BaseZigZagObject::getName() const
{
    return m_name;
}
