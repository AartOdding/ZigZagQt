#include "BaseZigZagObject.hpp"
#include "projectmodel.h"

#include "model/parameter/BaseParameter.hpp"

#include <QVector>
#include <QStringRef>


BaseZigZagObject::BaseZigZagObject(BaseZigZagObject * parent, const QString& name)
    : QObject(parent)
{
    setObjectName(name);
}


BaseZigZagObject::~BaseZigZagObject()
{
}


QString BaseZigZagObject::uniqueName() const
{
    auto object = this;
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


BaseZigZagObject* BaseZigZagObject::rootObject()
{
    auto root = this;

    while (qobject_cast<BaseZigZagObject*>(root->parent()))
    {
        root = static_cast<BaseZigZagObject*>(root->parent());
    }
    return root;
}


const BaseZigZagObject* BaseZigZagObject::rootObject() const
{
    auto root = this;

    while (qobject_cast<const BaseZigZagObject*>(root->parent()))
    {
        root = static_cast<const BaseZigZagObject*>(root->parent());
    }
    return root;
}


QObject* BaseZigZagObject::findObject(const QString& uniqueName)
{
    auto parts = uniqueName.splitRef('.', QString::KeepEmptyParts);
    QObject* root = rootObject();

    if (root && !parts.empty() && root->objectName() == parts[0])
    {
        QObject * object = root; // ProjectModel * with correct name.

        // Start at 1 cause 0 is the root which we already checked.
        for (int i = 1; i < parts.size(); ++i)
        {
            object = object->findChild<QObject*>(parts[i].toString(), Qt::FindDirectChildrenOnly);

            if (!object)
            {
                return nullptr;
            }
        }
        // If we reach here object should not be null and be an object matching uniqueName.
        return object;
    }
    return nullptr;
}


const QObject* BaseZigZagObject::findObject(const QString& uniqueName) const
{
    auto parts = uniqueName.splitRef('.', QString::KeepEmptyParts);
    const QObject* root = rootObject();

    if (root && !parts.empty() && root->objectName() == parts[0])
    {
        const QObject * object = root; // ProjectModel * with correct name.

        // Start at 1 cause 0 is the root which we already checked.
        for (int i = 1; i < parts.size(); ++i)
        {
            object = object->findChild<const QObject*>(parts[i].toString(), Qt::FindDirectChildrenOnly);

            if (!object)
            {
                return nullptr;
            }
        }
        // If we reach here object should not be null and be an object matching uniqueName.
        return object;
    }
    return nullptr;
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
