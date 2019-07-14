#include "operatorlibrary.h"

OperatorLibrary::OperatorLibrary()
{

}




void OperatorLibrary::add_operator_type(const std::string& operator_type, std::function<BaseOperator*()> create_function)
{
    if (creation_functions.count(operator_type) == 0)
    {
        creation_functions[operator_type] = create_function;
    }
}




BaseOperator* OperatorLibrary::create_operator(const std::string& operator_type)
{
    if (creation_functions.count(operator_type) == 1)
    {
        return creation_functions[operator_type]();
    }
    else
    {
        return nullptr;
    }
}


bool OperatorLibrary::contains_operator_type(const std::string& operator_type)
{
    return creation_functions.count(operator_type) == 1;
}
