#include "BaseZigZagObject.hpp"

#include "model/parameter/BaseParameter.hpp"



BaseZigZagObject::BaseZigZagObject(BaseZigZagObject * parent, const QString& name)
    : QObject(parent)
{
    setObjectName(name);
}


BaseZigZagObject::~BaseZigZagObject()
{

}


void BaseZigZagObject::updateParameters()
{
    auto children = findChildren<BaseZigZagObject*>(QString(), Qt::FindDirectChildrenOnly);

    for (auto child : children)
    {
        child->updateParameters();
    }
}


void BaseZigZagObject::disconnectParameters()
{
    auto children = findChildren<BaseZigZagObject*>(QString(), Qt::FindDirectChildrenOnly);

    for (auto child : children)
    {
        child->disconnectParameters();
    }
}


void BaseZigZagObject::parameterChangeEvent(const BaseParameter* parameter)
{
    BaseZigZagObject* parent = findParent<BaseZigZagObject*>();

    if (parent)
    {
        parent->parameterChangeEvent(parameter);
    }
}
