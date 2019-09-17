#pragma once

#include <vector>
#include <unordered_set>

#include <QObject>



class BaseParameter;


class ParameterOwner
{
public:

    static void reset_all_changed_flags();

    ParameterOwner(ParameterOwner *parent = nullptr);
    virtual ~ParameterOwner();

    const std::vector<BaseParameter*>& parameters() const;

    // Should not be necessary to be used by the user, called from BaseParameter.
    void register_parameter(BaseParameter* parameter);

    // Returns true if succesful
    bool deregister_parameter(BaseParameter* parameter);

    /*
    void flag_parameter_importing(BaseParameter * exporting_par);
    void flag_parameter_exporting(BaseParameter * importing_par);
    void flag_parameter_stopped_importing(BaseParameter * old_exporter);
    void flag_parameter_stopped_exporting(BaseParameter * old_importer);*/

    //void flag_parameters_connected(BaseParameter * exporter, BaseParameter * importer);
    //void flag_parameters_disconnected(BaseParameter * exporter, BaseParameter * importer);


    // Default implementation does not pass on the flag
    virtual void flag_parameters_changed();

    // Also resets all parameter's flags!
    void reset_changed_flags();

    bool parameters_changed() const;


    ParameterOwner * top_level_owner();

    const ParameterOwner * top_level_owner() const;

    // Undoable Action
    void remove_imports_exports();


//signals:

    //void parameter_started_importing(BaseParameter* exporter, BaseParameter * importer);
    //void parameter_stopped_importing(BaseParameter* exporter, BaseParameter * importer);


private:

    friend class ConnectParametersCommand;
    friend class DisconnectParametersCommand;

    static std::unordered_set<ParameterOwner*> all_parameter_owners;

    std::vector<BaseParameter*> m_parameters;

    ParameterOwner * parent = nullptr;

    bool m_changed = false;

};
