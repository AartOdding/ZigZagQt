#include "model/parameter/IntParameter.hpp"




IntParameter::IntParameter(BaseZigZagObject * parent, const QString& name, int64 value)
    : BaseParameter(ParameterType::Int, parent, name),
      m_value(this, name, value)
{
}



IntParameter::IntParameter(BaseZigZagObject * parent, const QString& name, int64 value, int64 min, int64 max)
    : BaseParameter(ParameterType::Int, parent, name),
      m_value(this, name, value, min, max)
{
}



int64 IntParameter::get() const
{
    return m_value.getValue();
}



int64 IntParameter::value() const
{
    return m_value.getValue();
}



void IntParameter::set(int64 value)
{
    m_value.setValue(value);
}



Int2Parameter::Int2Parameter(BaseZigZagObject * parent, const QString& name, int64_2 value)
    : BaseParameter(ParameterType::Int2, parent, name),
      m_xValue(this, QStringLiteral("X"), value[0]),
      m_yValue(this, QStringLiteral("Y"), value[1])
{
}



Int2Parameter::Int2Parameter(BaseZigZagObject * parent, const QString& name, int64_2 value, int64_2 min, int64_2 max)
    : BaseParameter(ParameterType::Int2, parent, name),
      m_xValue(this, QStringLiteral("X"), value[0], min[0], max[0]),
      m_yValue(this, QStringLiteral("Y"), value[1], min[1], max[1])
{
}



int64 Int2Parameter::x() const
{
    return m_xValue.getValue();
}



int64 Int2Parameter::y() const
{
    return m_yValue.getValue();
}



void Int2Parameter::setX(int64 x)
{
    m_xValue.setValue(x);
}



void Int2Parameter::setY(int64 y)
{
    m_yValue.setValue(y);
}



void Int2Parameter::set(int64 x, int64 y)
{
    m_xValue.setValue(x);
    m_yValue.setValue(y);
}



Int3Parameter::Int3Parameter(BaseZigZagObject * parent, const QString& name, int64_3 value)
    : BaseParameter(ParameterType::Int3, parent, name),
      m_xValue(this, QStringLiteral("X"), value[0]),
      m_yValue(this, QStringLiteral("Y"), value[1]),
      m_zValue(this, QStringLiteral("Z"), value[2])
{
}



Int3Parameter::Int3Parameter(BaseZigZagObject * parent, const QString& name, int64_3 value, int64_3 min, int64_3 max)
    : BaseParameter(ParameterType::Int3, parent, name),
      m_xValue(this, QStringLiteral("X"), value[0], min[0], max[0]),
      m_yValue(this, QStringLiteral("Y"), value[1], min[1], max[1]),
      m_zValue(this, QStringLiteral("Z"), value[2], min[2], max[2])
{
}



int64 Int3Parameter::x() const
{
    return m_xValue.getValue();
}



int64 Int3Parameter::y() const
{
    return m_yValue.getValue();
}



int64 Int3Parameter::z() const
{
    return m_zValue.getValue();
}



void Int3Parameter::setX(int64 x)
{
    m_xValue.setValue(x);
}



void Int3Parameter::setY(int64 y)
{
    m_yValue.setValue(y);
}



void Int3Parameter::setZ(int64 z)
{
    m_zValue.setValue(z);
}



void Int3Parameter::set(int64 x, int64 y, int64 z)
{
    m_xValue.setValue(x);
    m_yValue.setValue(y);
    m_zValue.setValue(z);
}



Int4Parameter::Int4Parameter(BaseZigZagObject * parent, const QString& name, int64_4 value)
    : BaseParameter(ParameterType::Int4, parent, name),
      m_xValue(this, QStringLiteral("X"), value[0]),
      m_yValue(this, QStringLiteral("Y"), value[1]),
      m_zValue(this, QStringLiteral("Z"), value[2]),
      m_wValue(this, QStringLiteral("W"), value[3])
{
}



Int4Parameter::Int4Parameter(BaseZigZagObject * parent, const QString& name, int64_4 value, int64_4 min, int64_4 max)
    : BaseParameter(ParameterType::Int4, parent, name),
      m_xValue(this, QStringLiteral("X"), value[0], min[0], max[0]),
      m_yValue(this, QStringLiteral("Y"), value[1], min[1], max[1]),
      m_zValue(this, QStringLiteral("Z"), value[2], min[2], max[2]),
      m_wValue(this, QStringLiteral("W"), value[3], min[3], max[3])
{
}



int64 Int4Parameter::x() const
{
    return m_xValue.getValue();
}



int64 Int4Parameter::y() const
{
    return m_yValue.getValue();
}



int64 Int4Parameter::z() const
{
    return m_zValue.getValue();
}



int64 Int4Parameter::w() const
{
    return m_wValue.getValue();
}



void Int4Parameter::setX(int64 x)
{
    m_xValue.setValue(x);
}



void Int4Parameter::setY(int64 y)
{
    m_yValue.setValue(y);
}



void Int4Parameter::setZ(int64 z)
{
    m_zValue.setValue(z);
}



void Int4Parameter::setW(int64 w)
{
    m_wValue.setValue(w);
}



void Int4Parameter::set(int64 x, int64 y, int64 z, int64 w)
{
    m_xValue.setValue(x);
    m_yValue.setValue(y);
    m_zValue.setValue(z);
    m_wValue.setValue(w);
}
