#include "EnumParameter.hpp"
#include "utility/numeric.h"



EnumParameter::EnumParameter(BaseZigZagObject * parent, const QString& name, const EnumDefinition& def, int i)
    : BaseParameter(ParameterType::Enum, parent, name),
      m_enum(&def),
      m_enumValue(this, name, i, 0, def.size()-1)
{
}


EnumParameter::EnumParameter(BaseZigZagObject * parent, const QString& name, const EnumDefinition& def, const QString& value)
    : BaseParameter(ParameterType::Enum, parent, name),
      m_enum(&def),
      m_enumValue(this, name, m_enum->index_of(value), 0, def.size()-1)
{
}


int EnumParameter::getIndex() const
{
    return static_cast<int>(m_enumValue.getValue());
}


const QString& EnumParameter::getText() const
{
    return m_enum->operator[](static_cast<int>(m_enumValue.getValue()));
}


const EnumDefinition * EnumParameter::getEnum() const
{
    return m_enum;
}


void EnumParameter::setIndex(int new_index)
{
    m_enumValue.change((int64_t)new_index);
}


void EnumParameter::setText(const QString& new_value)
{
    auto index = m_enum->index_of(new_value);

    if (index != -1)
    {
        setIndex(index);
    }
}


void EnumParameter::operator=(int new_index)
{
    setIndex(new_index);
}


void EnumParameter::operator=(const QString& new_value)
{
    setText(new_value);
}
