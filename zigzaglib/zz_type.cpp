#include "zz_type.h"

#include <QHash>


using IdNameMap = QHash<zz::TypeID, QString>;
using NameIdMap = QHash<QString, zz::TypeID>;


static IdNameMap& get_id_name_map()
{
    static IdNameMap map;
    return map;
}

static NameIdMap& get_name_id_map()
{
    static NameIdMap map;
    return map;
}


namespace zz
{

    RegisterType::RegisterType(TypeID type_id, const QString& type_name)
    {
        get_id_name_map().insert(type_id, type_name);
        get_name_id_map().insert(type_name, type_id);
    }


    namespace TypeRegistration
    {

        const QString& find_name(TypeID type_id)
        {
            auto it = get_id_name_map().find(type_id);

            if (it != get_id_name_map().end())
            {
                return it.value();
            }
            else
            {
                static QString empty_string;
                return empty_string;
            }
        }


        TypeID find_id(const QString& type_name)
        {
            auto it = get_name_id_map().find(type_name);

            if (it != get_name_id_map().end())
            {
                return it.value();
            }
            else
            {
                return 0;
            }
        }


        bool is_valid(TypeID type_id)
        {
            return get_id_name_map().contains(type_id);
        }


        bool is_valid(const QString& type_name)
        {
            return get_name_id_map().contains(type_name);
        }

    }

}
