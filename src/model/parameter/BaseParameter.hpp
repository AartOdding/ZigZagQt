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
    Color,
    Matrix3x3,
    Matrix4x4,
    Transform2D,
    Transform3D
};



class BaseParameter : public BaseZigZagObject
{
    Q_OBJECT

public:

    BaseParameter(ParameterType parameterType, BaseZigZagObject * parent, const QString& name);

    QList<BaseComponent*> getComponents() const;

    ParameterType getParameterType() const;

    /*
     * Shall update all the components and create parameterChange events on any changes.
     * More complex parameter types with multuiple sub parameters as children should override
     * this method to make sure
     */
    virtual void updateParameters() override;

private:

    ParameterType m_parameterType;

};


