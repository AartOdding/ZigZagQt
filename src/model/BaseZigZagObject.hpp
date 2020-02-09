#pragma once

#include <vector>

#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QXmlStreamAttributes>


class BaseParameter;
class OperatorNetwork;



class BaseZigZagObject : public QObject
{
    Q_OBJECT

public:

    BaseZigZagObject(BaseZigZagObject * parent, const QString& name);

    virtual ~BaseZigZagObject();

    /*
     * Will return the object's unique name. The unique name of an object consists of the
     * name of the object, preceded by every parent object's name. delimited by points.
     */
    QString uniqueName() const;

    /*
     * Will search for an object anywhere in the same object tree, with given unique name.
     */
    QObject* findObject(const QString& uniqueName);
    const QObject* findObject(const QString& uniqueName) const;

    /*
     * Will return the network this object belongs to, if any.
     */
    OperatorNetwork* network();
    const OperatorNetwork* network() const;

    /*
     * Will return the top most object in the tree hierarchy.
     */
    BaseZigZagObject* rootObject();
    const BaseZigZagObject* rootObject() const;

    /*
     * Will return the first parent than matches type PtrType.
     */
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

    /*
     * To allow things in ZigZag to load and store themselves to files, the readState and
     * writeState functions are used.
     */
    virtual void loadState(const QVariantMap&) { }

    /*
     * To allow things in ZigZag to load and store themselves to files, the readState and
     * writeState functions are used.
     */
    virtual QVariantMap storeState() const { return { }; }

    /*
     * Called when a child needs to be loaded, but the child does not yet exist.
     */
    virtual void createChild(const QXmlStreamAttributes&) { Q_ASSERT(false); } // Still need to implement!

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
    static_assert(std::is_pointer<PtrType>::value,
                  "Only pointer types are allowed!");
    static_assert(std::is_base_of<QObject, typename std::remove_pointer<PtrType>::type>::value,
                  "Type must be derived from QObject class!");

    QObject * p = parent();
    PtrType typeParent = nullptr;

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
