#include "EnumParameter.hpp"
#include "utility/numeric.h"



EnumPar::EnumPar(BaseZigZagObject * parent, const QString& name, const EnumDefinition& def, int i)
    : BaseParameter(ParameterType::Enum, parent, name),
      m_enum(&def),
      m_enumValue(this, i, 0, def.size()-1)
{
}


EnumPar::EnumPar(BaseZigZagObject * parent, const QString& name, const EnumDefinition& def, const QString& value)
    : BaseParameter(ParameterType::Enum, parent, name),
      m_enum(&def),
      m_enumValue(this, m_enum->index_of(value), 0, def.size()-1)
{
}


int EnumPar::getIndex() const
{
    return static_cast<int>(m_enumValue.getValue());
}


const QString& EnumPar::getText() const
{
    return m_enum->operator[](static_cast<int>(m_enumValue.getValue()));
}


const EnumDefinition * EnumPar::getEnum() const
{
    return m_enum;
}


void EnumPar::setIndex(int new_index)
{
    m_enumValue.change((int64_t)new_index);
}


void EnumPar::setText(const QString& new_value)
{
    auto index = m_enum->index_of(new_value);

    if (index != -1)
    {
        setIndex(index);
    }
}


void EnumPar::operator=(int new_index)
{
    setIndex(new_index);
}


void EnumPar::operator=(const QString& new_value)
{
    setText(new_value);
}
