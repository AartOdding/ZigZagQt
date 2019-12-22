#include "model/parameter/FloatParameter.hpp"




FloatParameter::FloatParameter(BaseZigZagObject * parent, const QString& name, double value)
    : BaseParameter(ParameterType::Int, parent, name),
      m_value(this, value)
{
    m_value.setObjectName(name);
}



FloatParameter::FloatParameter(BaseZigZagObject * parent, const QString& name, double value, double min, double max)
    : BaseParameter(ParameterType::Int, parent, name),
      m_value(this, value, min, max)
{
    m_value.setObjectName(name);
}



double FloatParameter::get() const
{
    return m_value.getValue();
}



double FloatParameter::value() const
{
    return m_value.getValue();
}



void FloatParameter::set(double value)
{
    m_value.setValue(value);
}



Float2Parameter::Float2Parameter(BaseZigZagObject * parent, const QString& name, double_2 value)
    : BaseParameter(ParameterType::Int2, parent, name),
      m_xValue(this, value[0]),
      m_yValue(this, value[1])
{
    m_xValue.setObjectName(QStringLiteral("X"));
    m_yValue.setObjectName(QStringLiteral("Y"));
}



Float2Parameter::Float2Parameter(BaseZigZagObject * parent, const QString& name, double_2 value, double_2 min, double_2 max)
    : BaseParameter(ParameterType::Int2, parent, name),
      m_xValue(this, value[0], min[0], max[0]),
      m_yValue(this, value[1], min[1], max[1])
{
    m_xValue.setObjectName(QStringLiteral("X"));
    m_yValue.setObjectName(QStringLiteral("Y"));
}



double Float2Parameter::x() const
{
    return m_xValue.getValue();
}



double Float2Parameter::y() const
{
    return m_yValue.getValue();
}



void Float2Parameter::setX(double x)
{
    m_xValue.setValue(x);
}



void Float2Parameter::setY(double y)
{
    m_yValue.setValue(y);
}



void Float2Parameter::set(double x, double y)
{
    m_xValue.setValue(x);
    m_yValue.setValue(y);
}



Float3Parameter::Float3Parameter(BaseZigZagObject * parent, const QString& name, double_3 value)
    : BaseParameter(ParameterType::Int3, parent, name),
      m_xValue(this, value[0]),
      m_yValue(this, value[1]),
      m_zValue(this, value[2])
{
    m_xValue.setObjectName(QStringLiteral("X"));
    m_yValue.setObjectName(QStringLiteral("Y"));
    m_zValue.setObjectName(QStringLiteral("Z"));
}



Float3Parameter::Float3Parameter(BaseZigZagObject * parent, const QString& name, double_3 value, double_3 min, double_3 max)
    : BaseParameter(ParameterType::Int3, parent, name),
      m_xValue(this, value[0], min[0], max[0]),
      m_yValue(this, value[1], min[1], max[1]),
      m_zValue(this, value[2], min[2], max[2])
{
    m_xValue.setObjectName(QStringLiteral("X"));
    m_yValue.setObjectName(QStringLiteral("Y"));
    m_zValue.setObjectName(QStringLiteral("Z"));
}



double Float3Parameter::x() const
{
    return m_xValue.getValue();
}



double Float3Parameter::y() const
{
    return m_yValue.getValue();
}



double Float3Parameter::z() const
{
    return m_zValue.getValue();
}



void Float3Parameter::setX(double x)
{
    m_xValue.setValue(x);
}



void Float3Parameter::setY(double y)
{
    m_yValue.setValue(y);
}



void Float3Parameter::setZ(double z)
{
    m_zValue.setValue(z);
}



void Float3Parameter::set(double x, double y, double z)
{
    m_xValue.setValue(x);
    m_yValue.setValue(y);
    m_zValue.setValue(z);
}



Float4Parameter::Float4Parameter(BaseZigZagObject * parent, const QString& name, double_4 value)
    : BaseParameter(ParameterType::Int4, parent, name),
      m_xValue(this, value[0]),
      m_yValue(this, value[1]),
      m_zValue(this, value[2]),
      m_wValue(this, value[3])
{
    m_xValue.setObjectName(QStringLiteral("X"));
    m_yValue.setObjectName(QStringLiteral("Y"));
    m_zValue.setObjectName(QStringLiteral("Z"));
    m_wValue.setObjectName(QStringLiteral("W"));
}



Float4Parameter::Float4Parameter(BaseZigZagObject * parent, const QString& name, double_4 value, double_4 min, double_4 max)
    : BaseParameter(ParameterType::Int4, parent, name),
      m_xValue(this, value[0], min[0], max[0]),
      m_yValue(this, value[1], min[1], max[1]),
      m_zValue(this, value[2], min[2], max[2]),
      m_wValue(this, value[3], min[3], max[3])
{
    m_xValue.setObjectName(QStringLiteral("X"));
    m_yValue.setObjectName(QStringLiteral("Y"));
    m_zValue.setObjectName(QStringLiteral("Z"));
    m_wValue.setObjectName(QStringLiteral("W"));
}



double Float4Parameter::x() const
{
    return m_xValue.getValue();
}



double Float4Parameter::y() const
{
    return m_yValue.getValue();
}



double Float4Parameter::z() const
{
    return m_zValue.getValue();
}



double Float4Parameter::w() const
{
    return m_wValue.getValue();
}



void Float4Parameter::setX(double x)
{
    m_xValue.setValue(x);
}



void Float4Parameter::setY(double y)
{
    m_yValue.setValue(y);
}



void Float4Parameter::setZ(double z)
{
    m_zValue.setValue(z);
}



void Float4Parameter::setW(double w)
{
    m_wValue.setValue(w);
}



void Float4Parameter::set(double x, double y, double z, double w)
{
    m_xValue.setValue(x);
    m_yValue.setValue(y);
    m_zValue.setValue(z);
    m_wValue.setValue(w);
}
