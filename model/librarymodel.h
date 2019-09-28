#pragma once

#include <string>
#include <unordered_map>


struct DataTypeInfo;
struct DataViewTypeInfo;
struct OperatorTypeInfo;



class LibraryModel
{

public:

    LibraryModel();

    void register_data_type(const DataTypeInfo* type);
    void register_data_type(const DataTypeInfo& type);

    void register_operator(const OperatorTypeInfo* type);
    void register_operator(const OperatorTypeInfo& type);

    //void register_data_view(const DataViewTypeInfo* type);
    //void register_data_view(const DataViewTypeInfo& type);

    //bool contains_view_for(const DataTypeInfo& data_type) const;


    std::vector<std::string> libraries() const;
    std::vector<const OperatorTypeInfo*> operators_for_library(const std::string& library) const;
    const OperatorTypeInfo* find_operator(const std::string& library, const std::string& name);

    const std::unordered_map<std::string, const DataTypeInfo*>& data_types() const;
    //const std::unordered_map<const DataTypeInfo*, const DataViewTypeInfo*>& data_views() const;


private:

    std::unordered_map<std::string, std::unordered_map<std::string, const OperatorTypeInfo*>> all_operators;

    std::unordered_map<std::string, const DataTypeInfo*> m_data_types;

    //std::unordered_map<const DataTypeInfo*, const DataViewTypeInfo*> m_data_views;

};
