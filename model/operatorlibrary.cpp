#include "operatorlibrary.h"

#include "baseoperator.h"
#include "basedatatype.h"
#include "view/basedataview.h"
#include "utility/std_containers_helpers.h"



OperatorLibrary* OperatorLibrary::instance()
{
    static OperatorLibrary library;
    return &library;
}


OperatorLibrary::OperatorLibrary()
{

}


void OperatorLibrary::add(const OperatorDescription* type)
{
    if (type)
    {
        operators[type->package][type->name] = type;
    }
}


void OperatorLibrary::add(const OperatorDescription& type)
{
    add(&type);
}


std::vector<std::string> OperatorLibrary::packages() const
{
    std::vector<std::string> result;
    result.reserve(operators.size());

    for (auto& [k, v] : operators)
    {
        result.emplace_back(k);
    }
    std::sort(result.begin(), result.end());

    return result;
}


std::vector<const OperatorDescription*> OperatorLibrary::get_package(const std::string& library) const
{
    std::vector<const OperatorDescription*> result;

    if (operators.count(library) > 0)
    {
        auto& lib_ops = operators.at(library);
        result.reserve(lib_ops.size());

        for (auto& [k, v] : lib_ops)
        {
            result.push_back(v);
        }

        std::sort(result.begin(), result.end(), [](auto a, auto b){ return *a < *b; });
    }
    return result;
}


const OperatorDescription* OperatorLibrary::get_operator(const std::string& library, const std::string& name)
{
    if (operators.count(library) > 0)
    {
        if (operators[library].count(name) > 0)
        {
            return operators[library][name];
        }
    }
    return nullptr;
}
