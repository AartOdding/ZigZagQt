#include "EnumParameter.hpp"
#include "utility/numericHelpers.hpp"



EnumParameter::EnumParameter(BaseZigZagObject * parent, const QString& name, const std::vector<QString>& values, int value)
    : BaseParameter(ParameterType::Enum, parent, name),
      m_enumComponent(this, name),
      m_possibleValues(values)
{
    m_enumComponent.setMin(0);
    m_enumComponent.setMax(values.size()-1);
    m_enumComponent.setValue(value);
}


EnumParameter::EnumParameter(BaseZigZagObject * parent, const QString& name, const std::vector<QString>& values, const QString& value)
    : EnumParameter(parent, name, values)
{
    m_enumComponent.setValue(indexOf(value));
}


int EnumParameter::getIndex() const
{
    return m_enumComponent.getValue();
}


const QString& EnumParameter::getValue() const
{
    static QString nullString;

    auto index = m_enumComponent.getValue();

    if (index >= 0 && index < m_possibleValues.size())
    {
        return m_possibleValues.at(index);
    }
    else
    {
        return nullString;
    }
}


const std::vector<QString>& EnumParameter::getPossibleValues() const
{
    return m_possibleValues;
}


int EnumParameter::indexOf(const QString& value) const
{
    for (int i = 0; i < m_possibleValues.size(); ++i)
    {
        if (m_possibleValues[i] == value)
        {
            return i;
        }
    }
    return -1;
}


const QString& EnumParameter::operator[](int index) const
{
    static QString nullString;

    if (index >= 0 && index < m_possibleValues.size())
    {
        return m_possibleValues.at(index);
    }
    else
    {
        return nullString;
    }
}


std::vector<QString>::const_iterator EnumParameter::begin() const
{
    return m_possibleValues.cbegin();
}


std::vector<QString>::const_iterator EnumParameter::end() const
{
    return m_possibleValues.cend();
}


void EnumParameter::set(int index)
{
    m_enumComponent.setValue(index);
}


void EnumParameter::set(const QString& value)
{
    m_enumComponent.setValue(indexOf(value));
}


void EnumParameter::addValue(const QString& value, int index)
{
    m_possibleValues.insert(m_possibleValues.begin() + index, value);
    emit enumValueAdded(value, index);
    emit enumValuesChanged(m_possibleValues);
}


bool EnumParameter::removeValue(int index)
{
    if (index >= 0 && index < m_possibleValues.size())
    {
        QString erasedValue = m_possibleValues[index];
        m_possibleValues.erase(m_possibleValues.begin() + index);
        emit enumValueRemoved(erasedValue, index);
        emit enumValuesChanged(m_possibleValues);
        return true;
    }
    return false;
}


bool EnumParameter::removeValue(const QString& value)
{
    int index = indexOf(value);

    if (index >= 0 && index < m_possibleValues.size())
    {
        m_possibleValues.erase(m_possibleValues.begin() + index);
        emit enumValueRemoved(value, index);
        emit enumValuesChanged(m_possibleValues);
        return true;
    }
    return false;
}
