#pragma once

#include <vector>
#include <unordered_set>

#include <QObject>



class BaseParameter;


class ParameterOwner : public QObject
{
    Q_OBJECT

public:

    static void reset_all_changed_flags();


    ParameterOwner(ParameterOwner *parent = nullptr);

    ~ParameterOwner();


    const std::vector<BaseParameter*>& parameters() const;

    // Should not be necessary to be used by the user, called from BaseParameter.
    void register_parameter(BaseParameter* parameter);

    // Returns true if succesful
    bool deregister_parameter(BaseParameter* parameter);


    void flag_parameter_connection(BaseParameter * exporter, BaseParameter * importer);

    void flag_parameter_disconnection(BaseParameter * exporter, BaseParameter * importer);


    // Default implementation does not pass on the flag
    virtual void flag_parameters_changed();

    // Also resets all parameter's flags!
    void reset_changed_flags();

    bool parameters_changed() const;


    ParameterOwner * top_level_owner();

    const ParameterOwner * top_level_owner() const;

    // Undoable Action
    void remove_imports_exports();


signals:

    void parameter_added(BaseParameter* parameter);

    void parameter_removed(BaseParameter* parameter);

    void parameters_connected(BaseParameter* exporter, BaseParameter * importer);

    void parameters_disconnected(BaseParameter* exporter, BaseParameter * importer);

protected:

    std::vector<BaseParameter*> m_parameters;


private:

    static std::unordered_set<ParameterOwner*> all_parameter_owners;

    bool m_changed = false;

    ParameterOwner * parent = nullptr;

};
