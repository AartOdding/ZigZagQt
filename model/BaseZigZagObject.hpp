#pragma once

#include <vector>
#include <QString>
#include <QObject>


class BaseParameter;



class BaseZigZagObject
{
public:

    BaseZigZagObject() = delete;
    BaseZigZagObject(BaseZigZagObject&&) = default;
    BaseZigZagObject(const BaseZigZagObject&) = delete;
    BaseZigZagObject(BaseZigZagObject * parent, const QString& name);

    virtual ~BaseZigZagObject();

    BaseZigZagObject * getParent();
    const BaseZigZagObject * getParent() const;

    std::vector<BaseZigZagObject*> getChildren();
    const std::vector<BaseZigZagObject*>& getChildren() const;

    std::vector<BaseParameter*> getParameters();
    const std::vector<BaseParameter*>& getParameters() const;

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

