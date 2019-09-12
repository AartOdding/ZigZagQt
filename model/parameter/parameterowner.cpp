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


ParameterOwner::ParameterOwner(ParameterOwner *parent_)
    : QObject(parent_), parent(parent_)
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


void ParameterOwner::flag_parameter_connection(BaseParameter * exporter, BaseParameter * importer)
{
    if (exporter && importer)
    {
        emit parameters_connected(exporter, importer);
    }
}


void ParameterOwner::flag_parameter_disconnection(BaseParameter * exporter, BaseParameter * importer)
{
    if (exporter && importer)
    {
        emit parameters_disconnected(exporter, importer);
    }
}


ParameterOwner * ParameterOwner::top_level_owner()
{
    return parent ? parent->top_level_owner() : this;
}


const ParameterOwner * ParameterOwner::top_level_owner() const
{
    return parent ? parent->top_level_owner() : this;
}


void ParameterOwner::remove_imports_exports()
{
    for (auto par : m_parameters)
    {
        par->remove_import();

        for (auto e : par->get_exports())
        {
            e->remove_import();
        }
    }
}
