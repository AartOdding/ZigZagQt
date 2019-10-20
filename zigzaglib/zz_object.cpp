#include "zz_object.h"

#include <algorithm>



namespace zz
{


    BaseObject::BaseObject(TypeID type_id_, BaseObject * parent_)
        : type_id(type_id_), parent(parent_)

    {
        Q_ASSERT(TypeRegistration::is_valid(type_id));

        if (parent)
        {
            parent->children.push_back(this);
        }
    }


    BaseObject::~BaseObject()
    {
        if (parent)
        {
            auto pos = std::find(parent->children.begin(), parent->children.end(), this);

            Q_ASSERT(pos != parent->children.end());

            // Order is not important, swap pos with last element, and erase.
            std::iter_swap(pos, parent->children.rbegin());
            parent->children.pop_back();
        }
    }


    const QString& BaseObject::get_name() const
    {
        return name;
    }


    const QString& BaseObject::get_type_name() const
    {
        return TypeRegistration::find_name(type_id);
    }


    TypeID BaseObject::get_type_id() const
    {
        return type_id;
    }


    BaseObject * BaseObject::get_parent() const
    {
        return parent;
    }


    const std::vector<BaseObject*>& BaseObject::get_children() const
    {
        return children;
    }


    void BaseObject::serialize() const
    {

    }


    void BaseObject::deserialize() const
    {

    }


}
