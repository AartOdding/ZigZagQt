#include "parameterowner.h"
#include "baseparameter.h"
#include "model/baseoperator.h"
#include "utility/std_containers_helpers.h"



ParameterOwner::ParameterOwner(ParameterOwner * owner, const char * name)
    : BaseParameter(owner, ParameterType::ParameterOwner, name)
{
}


const std::vector<BaseParameter*>& ParameterOwner::get_parameters() const
{
    return parameters;
}


void ParameterOwner::process_parameter_changes()
{
    for (auto parameter : parameters)
    {
        parameter->process_parameter_changes();
    }
}


bool ParameterOwner::is_operator() const
{
    //Q_ASSERT(dynamic_cast<const BaseOperator*>(this) != nullptr);
    return get_parent() == nullptr;
}


void ParameterOwner::remove_imports_exports()
{
    for (auto parameter : parameters)
    {
        parameter->remove_imports_exports();
    }
}


void ParameterOwner::register_parameter(BaseParameter* parameter)
{
    if (parameter)
    {
        if (!contains(parameters, parameter))
        {
            parameters.push_back(parameter);
        }
    }
}


bool ParameterOwner::deregister_parameter(BaseParameter* parameter)
{
    if (parameter)
    {
        auto pos = std::find(parameters.begin(), parameters.end(), parameter);

        if (pos != parameters.end())
        {
            parameters.erase(pos);
            return true;
        }
    }
    return false;
}
