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


    ParameterOwner(QObject *parent = nullptr);

    ~ParameterOwner();


    const std::vector<BaseParameter*>& parameters() const;

    // Should not be necessary to be used by the user, called from BaseParameter.
    void register_parameter(BaseParameter* parameter);

    // Returns true if succesful
    bool deregister_parameter(BaseParameter* parameter);


    void flag_parameters_changed();

    // Also resets all parameter's flags!
    void reset_changed_flags();

    bool parameters_changed() const;


signals:

    void parameter_added(BaseParameter* parameter);

    void parameter_removed(BaseParameter* parameter);


protected:

    std::vector<BaseParameter*> m_parameters;


private:

    static std::unordered_set<ParameterOwner*> all_parameter_owners;

    bool m_changed = false;

};
