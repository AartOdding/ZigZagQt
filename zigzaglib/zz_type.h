#pragma once

#include <QString>
#include <QtGlobal>



namespace zz
{

    /*
     * All Types in ZigZag shall have their own unique type id.
     * A type id is an 64 bit unsigned integer.
     * The numbers 0 - 1000000 (one million) are reserved for
     * usage by ZigZag.
     */

    using TypeID = quint64;



    struct RegisterType
    {
        RegisterType(TypeID type_id, const QString& type_name);
    };



    namespace TypeRegistration
    {

        const QString& find_name(TypeID type_id);

        TypeID find_id(const QString& type_name);

        bool is_valid(TypeID type_id);

        bool is_valid(const QString& type_name);

    };


}
