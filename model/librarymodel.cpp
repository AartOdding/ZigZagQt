#include "librarymodel.h"

#include "baseoperator.h"
#include "basedatatype.h"

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



bool LibraryModel::contains_operator(const std::string& name) const
{
    return m_operators.count(name) > 0;
}

const std::unordered_map<std::string, const DataTypeInfo*>& LibraryModel::data_types() const
{
    return m_data_types;
}

const std::unordered_map<std::string, const OperatorTypeInfo*>& LibraryModel::operators() const
{
    return m_operators;
}


/*
BaseOperator* LibraryModel::create_operator(const std::string& operator_type)
{
    if (creation_functions.count(operator_type) > 0)
    {
        return creation_functions[operator_type]();
    }
    else
    {
        return nullptr;
    }
}


bool LibraryModel::contains_operator_type(const std::string& operator_type)
{
    return creation_functions.count(operator_type) == 1;
}*/
