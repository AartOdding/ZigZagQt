#pragma once

#include <string>
#include <unordered_map>


struct DataTypeInfo;
struct DataViewTypeInfo;
struct OperatorDescription;



class OperatorLibrary
{

public:

    static OperatorLibrary* instance();

    void add(const OperatorDescription* type);
    void add(const OperatorDescription& type);

    std::vector<std::string> packages() const;

    std::vector<const OperatorDescription*> get_package(const std::string& package) const;

    const OperatorDescription* get_operator(const std::string& package, const std::string& name);


private:

    OperatorLibrary();

    std::unordered_map<std::string, std::unordered_map<std::string, const OperatorDescription*>> operators;

};
