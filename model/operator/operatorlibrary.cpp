#include "operatorlibrary.h"

OperatorLibrary::OperatorLibrary()
{

}


void OperatorLibrary::add_operator_type(const std::string& operator_name, std::function<BaseOperator*()> create_function)
{
    if (creation_functions.count(operator_name) == 0)
    {
        creation_functions[operator_name] = create_function;
    }
}


BaseOperator* OperatorLibrary::create_operator(const std::string& operator_name)
{
    if (creation_functions.count(operator_name) == 1)
    {
        return creation_functions[operator_name]();
    }
    else {
        return nullptr;
    }
}
