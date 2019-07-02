#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#include "model/operator/baseoperator.h"



class OperatorLibrary
{

public:


    OperatorLibrary();

    /*
     * create_function can either be a static member function, a free function,
     * a member function that has bound arguments with std::bind, or a free function
     * with bound arguments.
     */
    void add_operator_type(const std::string& operator_name, std::function<BaseOperator*()> create_function);

    BaseOperator* create_operator(const std::string& operator_name);


private:

    std::unordered_map<std::string, std::function<BaseOperator*()>> creation_functions;


};
