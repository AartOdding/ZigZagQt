#pragma once

#include <vector>
#include <QString>
#include <QObject>


class BaseParameter;
class QXmlStreamReader;
class XmlSerializer;



class BaseZigZagObject
{
public:

    BaseZigZagObject() = delete;
    BaseZigZagObject(BaseZigZagObject&&) = default;
    BaseZigZagObject(const BaseZigZagObject&) = delete;
    BaseZigZagObject(BaseZigZagObject * parent, const QString& name, bool isParameter = false);

    virtual ~BaseZigZagObject();

    BaseZigZagObject * getParent();
    const BaseZigZagObject * getParent() const;

    BaseZigZagObject * getTopParent();
    const BaseZigZagObject * getTopParent() const;

    template<typename Type>
    Type * findParent();
    template<typename Type>
    const Type * findParent() const;

    std::vector<BaseZigZagObject*> getChildren();
    const std::vector<BaseZigZagObject*>& getChildren() const;

    std::vector<BaseParameter*> getParameters();
    const std::vector<BaseParameter*>& getParameters() const;

    const QString& getName() const;

    /*
     * updateParameters() will call the update() function on every parameter that it has.
     * If 'recursive' is true, it will also recursively call updateParameters() on all of
     * its children.
     */
    void updateParameters(bool recursive = true);

    /*
     * disconnectParameters() will call the disconnect() function on every parameter it has.
     * If 'recursive' is true it will also recursively call disconnectParameters() on all of
     * its children.
     */
    void disconnectParameters(bool recursive = true);

protected:

    /*
     * parameterChangeEvent() is called when one of this object's parameter's values
     * has been changed as a result of calling updateParameters(). The default implementation
     * will check if there is a parent, and if so forward the event to them.
     */
    virtual void parameterChangeEvent(const BaseParameter* parameter);

private:

    BaseZigZagObject * m_parent = nullptr;
    std::vector<BaseParameter*> m_parameters;
    std::vector<BaseZigZagObject*> m_children;
    QString m_name;

};




template<typename Type>
Type * BaseZigZagObject::findParent()
{
    BaseZigZagObject * parent = m_parent;
    Type * typeParent;

    while (parent)
    {
        typeParent = dynamic_cast<Type*>(parent);

        if (typeParent)
        {
            break;
        }
        else
        {
            parent = parent->m_parent;
        }
    }
    return typeParent;
}


template<typename Type>
const Type * BaseZigZagObject::findParent() const
{
    const BaseZigZagObject * parent = m_parent;
    const Type * typeParent;

    while (parent)
    {
        typeParent = dynamic_cast<Type*>(parent);

        if (typeParent)
        {
            break;
        }
        else
        {
            parent = parent->m_parent;
        }
    }
    return typeParent;
}
