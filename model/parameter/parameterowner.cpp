#include "parameterowner.h"


ParameterOwner::ParameterOwner(QObject *parent)
    : QObject(parent)
{

}


const std::vector<BaseParameter*>& ParameterOwner::parameters() const
{
    return m_parameters;
}


void ParameterOwner::register_parameter(BaseParameter* parameter)
{
    if (parameter)
    {
        if (std::find(m_parameters.begin(), m_parameters.end(), parameter) == m_parameters.end())
        {
            m_parameters.push_back(parameter);
            emit parameter_added(parameter);
        }
    }
}
