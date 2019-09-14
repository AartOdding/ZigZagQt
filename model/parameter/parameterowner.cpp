#include "parameterowner.h"
#include "model/baseoperator.h"
#include "baseparameter.h"
#include "utility/std_containers_helpers.h"


std::unordered_set<ParameterOwner*> ParameterOwner::all_parameter_owners;


void ParameterOwner::reset_all_changed_flags()
{
    for (auto owner : all_parameter_owners)
    {
        owner->reset_changed_flags();
    }
}


ParameterOwner::ParameterOwner(ParameterOwner *parent_)
    : parent(parent_)
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

/*
void ParameterOwner::flag_parameters_connected(BaseParameter * exporter, BaseParameter * importer)
{
    Q_ASSERT(exporter && importer);

    if (exporter->parent_operator() == this)
    {
        m_exporting_parameters.push_back(exporter);
    }
    if (importer->parent_operator() == this)
    {
        m_importing_parameters.push_back(importer);
        emit parameter_started_importing(exporter, importer);
    }
}


void ParameterOwner::flag_parameters_disconnected(BaseParameter * exporter, BaseParameter * importer)
{
    Q_ASSERT(exporter && importer);

    if (exporter->parent_operator() == this)
    {
        try_erase(m_exporting_parameters, exporter);
    }
    if (importer->parent_operator() == this)
    {
        try_erase(m_importing_parameters, importer);
        emit parameter_stopped_importing(exporter, importer);
    }
}*/

/*
void ParameterOwner::flag_parameter_importing(BaseParameter * exporting_par)
{
    Q_ASSERT(exporting_par);
    Q_ASSERT(!contains(m_importing_parameters, this));

    m_importing_parameters.push_back(importer);
    emit parameter_importing(importer);
}


void ParameterOwner::flag_parameter_exporting(BaseParameter * importing_par)
{
    Q_ASSERT(exporter);
    Q_ASSERT(!contains(m_exporting_parameters, exporter));

    m_exporting_parameters.push_back(exporter);
    emit parameter_exporting(exporter);
}


void ParameterOwner::flag_parameter_stopped_importing(BaseParameter * old_exporter)
{
    Q_ASSERT(importer);
    Q_ASSERT(contains(m_importing_parameters, importer));

    try_erase(m_importing_parameters, importer);
    emit parameter_stopped_importing(importer);
}


void ParameterOwner::flag_parameter_stopped_exporting(BaseParameter * old_importer)
{
    Q_ASSERT(exporter);
    Q_ASSERT(contains(m_exporting_parameters, exporter));

    try_erase(m_exporting_parameters, exporter);
    emit parameter_stopped_exporting(exporter);
}*/


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
