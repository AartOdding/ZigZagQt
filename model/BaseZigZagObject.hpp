#pragma once

#include <vector>
#include <QString>
#include <QObject>


class BaseParameter;
class QXmlStreamReader;
class XmlSerializer;



class BaseZigZagObject : public QObject
{
    Q_OBJECT

public:

    BaseZigZagObject(BaseZigZagObject * parent, const QString& name);

    virtual ~BaseZigZagObject();


    template<typename PtrType>
    PtrType findParent(bool directParentOnly = false) const;

    /*
     * When calling updateParameters(), it will be called recursively for all children of
     * this object. The default implementation will only do that (call updateParameters()
     * on all the children), however parameter objects can overload this method to
     * update all their components, and fire of parameterChange events on changes.
     */
    virtual void updateParameters();

    /*
     * When calling disconnectParameters() it will be called recursively for all children of
     * this object. The default implementation does not actually disconnect anything, but only
     * ensures that disconnectParameters is called for all the children. Overloaded versions
     * of this method can make sure components are actually diconnected.
     */
    virtual void disconnectParameters();

protected:

    /*
     * parameterChangeEvent() is called when one of this object's parameter's values
     * has been changed as a result of calling updateParameters(). The default implementation
     * will check if there is a parent, and if so forward the event to them.
     */
    virtual void parameterChangeEvent(const BaseParameter* parameter);

};



template<typename PtrType>
PtrType BaseZigZagObject::findParent(bool directParentOnly) const
{
    QObject * p = parent();
    PtrType typeParent;

    while (p)
    {
        typeParent = qobject_cast<PtrType>(p);

        if (typeParent || directParentOnly)
        {
            break;
        }
        else
        {
            p = p->parent();
        }
    }
    return typeParent;
}
