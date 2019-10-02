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


    // Will recurively call remove_imports_exports on all its children.
    virtual void remove_imports_exports() override;

    // Will recursively call children
    virtual void process_parameter_changes() override;

    // Called when one of the owned parameters, or one of their children changed.
    virtual void parameter_changed(BaseParameter*) { }



    bool is_operator() const;


    virtual int num_components() const override { return 0; }

    virtual BaseParameterComponent* get_component(int) override { return nullptr; }

    virtual const BaseParameterComponent* get_component(int) const override { return nullptr; }


private:

    friend class BaseParameter;

    // Called from BaseParameter constructor.
    void register_parameter(BaseParameter* parameter);

    // Called from BaseParameter destructor, returns true if succesful.
    bool deregister_parameter(BaseParameter* parameter);


    std::vector<BaseParameter*> parameters;


};
