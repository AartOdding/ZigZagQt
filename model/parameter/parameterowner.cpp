#include "parameterowner.h"
#include "baseparameter.h"

std::unordered_set<ParameterOwner*> ParameterOwner::all_parameter_owners;


void ParameterOwner::reset_all_changed_flags()
{
    for (auto owner : all_parameter_owners)
    {
        owner->reset_changed_flags();
    }
}


ParameterOwner::ParameterOwner(QObject *parent)
    : QObject(parent)
{
    all_parameter_owners.insert(this);
}


ParameterOwner::~ParameterOwner()
{
    all_parameter_owners.erase(this);
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


// Returns true if succesful
bool ParameterOwner::deregister_parameter(BaseParameter* parameter)
{
    if (parameter)
    {
        auto pos = std::find(m_parameters.begin(), m_parameters.end(), parameter);
        if (pos != m_parameters.end())
        {
            m_parameters.erase(pos);
            emit parameter_removed(parameter);
            return true;
        }
    }
    return false;
}


void ParameterOwner::flag_parameters_changed()
{
    m_changed = true;
}


void ParameterOwner::reset_changed_flags()
{
    m_changed = false;

    for (auto par : m_parameters)
    {
        par->reset_changed_flag();
    }
}


bool ParameterOwner::parameters_changed() const
{
    return m_changed;
}
