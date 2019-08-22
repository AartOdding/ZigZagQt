#pragma once

#include <string>
#include <unordered_map>


struct DataTypeInfo;
struct OperatorTypeInfo;



class LibraryModel
{

public:


    LibraryModel();


    void register_data_type(const DataTypeInfo* type);
    void register_data_type(const DataTypeInfo& type);

    void register_operator(const OperatorTypeInfo* type);
    void register_operator(const OperatorTypeInfo& type);

    bool contains_operator(const std::string& name) const;
/*
    BaseOperator* create_operator(const std::string& operator_type);


    bool contains_operator_type(const std::string& operator_type);

*/

    const std::unordered_map<std::string, const DataTypeInfo*>& data_types() const;

    const std::unordered_map<std::string, const OperatorTypeInfo*>& operators() const;



private:

    std::unordered_map<std::string, const DataTypeInfo*> m_data_types;

    std::unordered_map<std::string, const OperatorTypeInfo*> m_operators;

};
