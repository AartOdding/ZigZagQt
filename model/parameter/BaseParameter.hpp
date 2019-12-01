#pragma once

#include <vector>
#include <QString>

#include "model/BaseZigZagObject.hpp"
#include "model/parameter/baseparameterold.h"

class BaseComponent;



class BaseParameter : public BaseZigZagObject
{
public:

    BaseParameter() = delete;
    BaseParameter(BaseParameter&&) = default;
    BaseParameter(const BaseParameter&) = delete;
    BaseParameter(ParameterType parameterType, BaseZigZagObject * parent, const QString& name);

    std::vector<BaseComponent*> getComponents();
    const std::vector<BaseComponent*>& getComponents() const;

    ParameterType getParameterType() const;

    /*
     * Shall update the child parameters and components. Will return true if atleast one parameter/
     * component changed. If silent is true no events will be generated fromthe changes.
     */
    virtual bool update(bool silent = false);

    // Shall disconnect all parameters
    void disconnectParameters(bool recursive = true);

private:

    friend class BaseComponent;

    ParameterType m_parameterType;

    // components will add and remove themselves in their constructor/ destructor
    std::vector<BaseComponent*> m_components;

};

