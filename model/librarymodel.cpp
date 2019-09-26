#include "librarymodel.h"

#include "baseoperator.h"
#include "basedatatype.h"
#include "view/basedataview.h"
#include "utility/std_containers_helpers.h"



LibraryModel::LibraryModel()
{

}


void LibraryModel::register_data_type(const DataTypeInfo* type)
{
    if (type)
    {
        m_data_types[type->name] = type;
    }
}


void LibraryModel::register_data_type(const DataTypeInfo& type)
{
    register_data_type(&type);
}


void LibraryModel::register_operator(const OperatorTypeInfo* type)
{
    if (type)
    {
        all_operators[type->library][type->name] = type;
    }
}


void LibraryModel::register_operator(const OperatorTypeInfo& type)
{
    register_operator(&type);
}

/*
void LibraryModel::register_data_view(const DataViewTypeInfo* view_type)
{
    if (view_type && view_type->data_type)
    {
        m_data_views[view_type->data_type] = view_type;
    }
}


void LibraryModel::register_data_view(const DataViewTypeInfo& type)
{
    register_data_view(&type);
}


bool LibraryModel::contains_view_for(const DataTypeInfo& data_type) const
{
    return m_data_views.count(&data_type) > 0;
}*/


std::vector<const char *> LibraryModel::libraries() const
{
    std::vector<const char*> result;
    result.reserve(all_operators.size());

    for (auto& [k, v] : all_operators)
    {
        result.emplace_back(k.c_str());
    }
    return result;
}


std::vector<const OperatorTypeInfo*> LibraryModel::operators_for_library(const std::string& library) const
{
    std::vector<const OperatorTypeInfo*> result;

    if (all_operators.count(library) > 0)
    {
        auto& lib_ops = all_operators.at(library);
        result.reserve(lib_ops.size());

        for (auto& [k, v] : lib_ops)
        {
            result.push_back(v);
        }
    }
    return result;
}


const OperatorTypeInfo* LibraryModel::find_operator(const std::string& library, const std::string& name)
{
    if (all_operators.count(library) > 0)
    {
        if (all_operators[library].count(name) > 0)
        {
            return all_operators[library][name];
        }
    }
    return nullptr;
}


const std::unordered_map<std::string, const DataTypeInfo*>& LibraryModel::data_types() const
{
    return m_data_types;
}

/*
const std::unordered_map<const DataTypeInfo*, const DataViewTypeInfo*>& LibraryModel::data_views() const
{
    return m_data_views;
}*/
