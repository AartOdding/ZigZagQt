#pragma once

#include <vector>

#include "baseparameter.h"




class ParameterOwner : public BaseParameter
{
public:

    // Parent should be nullptr if 'this' is the operator.
    ParameterOwner(ParameterOwner * parent, const char * name);

    virtual ~ParameterOwner() override = default;


    const std::vector<BaseParameter*>& get_parameters() const;


    virtual void remove_imports_exports() override;

    // Will recursively call children
    virtual void process_parameter_changes() override;

    // Return true if the parameter change was acepted, when false is returned
    // the parameter change event will be passed on to the owner of this ParameterOwner
    virtual bool parameter_changed(BaseParameter*) { return false; }



    bool is_operator() const;


    virtual int num_components() const override { return 0; }

    virtual ParameterComponent* get_component(int) override { return nullptr; }

    virtual const ParameterComponent* get_component(int) const override { return nullptr; }


private:

    friend class BaseParameter;

    // Called from BaseParameter constructor.
    void register_parameter(BaseParameter* parameter);

    // Called from BaseParameter destructor, returns true if succesful.
    bool deregister_parameter(BaseParameter* parameter);


    std::vector<BaseParameter*> parameters;


};
