#include "librarymodel.h"

#include "baseoperator.h"
#include "basedatatype.h"
#include "view/basedataview.h"


LibraryModel::LibraryModel()
{

}


void LibraryModel::register_data_type(const DataTypeInfo* type)
{
    if (type)
    {
        if (m_data_types.count(type->name) == 0)
        {
            m_data_types[type->name] = type;
        }
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
        if (m_operators.count(type->name) == 0)
        {
            m_operators[type->name] = type;
        }
    }
}


void LibraryModel::register_operator(const OperatorTypeInfo& type)
{
    register_operator(&type);
}


void LibraryModel::register_data_view(const DataViewTypeInfo* view_type)
{
    auto data_type = view_type->data_type;

    if (view_type && data_type)
    {
        // Only one view per data_type supported as of now.
        if (m_data_views.count(data_type) == 0)
        {
            m_data_views[data_type] = view_type;
        }
    }
}


void LibraryModel::register_data_view(const DataViewTypeInfo& type)
{
    register_data_view(&type);
}


bool LibraryModel::contains_operator(const std::string& name) const
{
    return m_operators.count(name) > 0;
}


bool LibraryModel::contains_view_for(const DataTypeInfo& data_type) const
{
    return m_data_views.count(&data_type) > 0;
}


const std::unordered_map<std::string, const DataTypeInfo*>& LibraryModel::data_types() const
{
    return m_data_types;
}


const std::unordered_map<std::string, const OperatorTypeInfo*>& LibraryModel::operators() const
{
    return m_operators;
}


const std::unordered_map<const DataTypeInfo*, const DataViewTypeInfo*>& LibraryModel::data_views() const
{
    return m_data_views;
}
