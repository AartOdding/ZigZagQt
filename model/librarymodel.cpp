#include "librarymodel.h"

LibraryModel::LibraryModel()
{

}




void LibraryModel::add_operator_type(const std::string& operator_type, std::function<BaseOperator*()> create_function)
{
    if (creation_functions.count(operator_type) == 0)
    {
        creation_functions[operator_type] = create_function;
    }
}




BaseOperator* LibraryModel::create_operator(const std::string& operator_type)
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


bool LibraryModel::contains_operator_type(const std::string& operator_type)
{
    return creation_functions.count(operator_type) == 1;
}
