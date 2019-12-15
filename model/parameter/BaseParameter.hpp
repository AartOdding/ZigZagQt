#pragma once

#include <vector>
#include <QString>

#include "model/BaseZigZagObject.hpp"


class BaseComponent;


enum class ParameterType
{
    Int,
    Int2,
    Int3,
    Int4,
    Float,
    Float2,
    Float3,
    Float4,
    Enum,
    Button,
    Matrix3x3,
    Matrix4x4,
};



class BaseParameter : public BaseZigZagObject
{
    Q_OBJECT

public:

    BaseParameter(ParameterType parameterType, BaseZigZagObject * parent, const QString& name);

    std::vector<BaseComponent*> getComponents();
    const std::vector<BaseComponent*>& getComponents() const;

    ParameterType getParameterType() const;

    /*
     * Shall update the child parameters and components. Will return true if atleast one parameter/
     * component changed. If silent is true no events will be generated from the changes.
     */
    virtual bool update(bool silent = false);

    // Shall disconnect all parameters
    void disconnectParameters(bool recursive = true);

private:

    friend class BaseComponent;

    // components will add and remove themselves in their constructor/ destructor
    std::vector<BaseComponent*> m_components;

    ParameterType m_parameterType;

};

//Q_DECLARE_METATYPE(BaseParameter*);

