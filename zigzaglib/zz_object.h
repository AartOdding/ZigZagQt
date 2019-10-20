#pragma once

#include <vector>
#include <QString>

#include "zz_type.h"


namespace zz
{

    class BaseObject
    {

    public:

        BaseObject(TypeID type_id, BaseObject * parent = nullptr);

        virtual ~BaseObject();


        const QString& get_name() const;

        const QString& get_type_name() const;

        TypeID get_type_id() const;


        BaseObject * get_parent() const;

        const std::vector<BaseObject*>& get_children() const;


        virtual void serialize() const;

        virtual void deserialize() const;


    private:

        TypeID type_id;
        QString name;
        BaseObject * parent;
        std::vector<BaseObject*> children;

    };


}

