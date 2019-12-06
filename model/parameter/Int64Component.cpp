#include "Int64Component.hpp"
#include "utility/numeric.h"
#include "zigzaglib/xmlserializer.h"

#include <numeric>




Int64Component::Int64Component(BaseParameter* parameter, int64_t value)
    : Int64Component(parameter, value, std::numeric_limits<int64_t>::lowest(), std::numeric_limits<int64_t>::max())
{

}



Int64Component::Int64Component(BaseParameter* parameter, int64_t value, int64_t min, int64_t max)
    : BaseComponent(parameter)
{
    m_min = smallest(min, max);
    m_max = largest(min, max);
    m_value = constrain(value, m_min, m_max);
}



bool Int64Component::update()
{
    if (m_newValuePending)
    {
        return setValue(m_pending, true);
    }
    return false;
}



int64_t Int64Component::getValue() const
{
    return m_value;
}



int64_t Int64Component::getMin() const
{
    return m_min;
}



int64_t Int64Component::getMax() const
{
    return m_max;
}



bool Int64Component::setValue(int64_t value, bool overwritePendingChanges)
{
    if (overwritePendingChanges)
    {
        m_newValuePending = false;
    }

    int64_t constrained_value = constrain(value, m_min, m_max);

    if (constrained_value != m_value)
    {
        m_value = constrained_value;
        emit valueChanged(m_value);
        return true;
    }
    return false;
}



void Int64Component::setMin(int64_t min)
{
    int64_t new_min = smallest(min, m_max); // Min shall not be larger than max.

    if (m_min != new_min)
    {
        m_min = new_min;

        setValue(m_value, false); // Min could have been increased to higher than m_value ...

        // Emit after value changed is emitted, otherwise we can get a situation where value
        // can be lower than min.
        emit minChanged(m_min);
    }
}



void Int64Component::setMax(int64_t max)
{
    int64_t new_max = largest(max, m_min); // Max shall not be smaller than min.

    if (m_max != new_max)
    {
        m_max = new_max;

        setValue(m_value, false); // Max could have been decreased to less than m_value ...

        // Emit after value changed is emitted, otherwise we can get a situation where value
        // can be higher than max.
        emit maxChanged(m_max);
    }
}



void Int64Component::change(int64_t value)
{
    m_pending = value;
    m_newValuePending = m_pending != m_value;
}



void Int64Component::change(double value)
{
    m_pending = value;
    m_newValuePending = m_pending != m_value;
}



void Int64Component::readXml(QXmlStreamReader& xml)
{

}



void Int64Component::writeXml(XmlSerializer& xml)
{
    xml.begin_element("IntParameterComponent");

        BaseComponent::writeXml(xml);

        xml.add_int_element("current_value", m_value);
        xml.add_int_element("min_value", m_min);
        xml.add_int_element("max_value", m_max);
        xml.add_int_element("pending_value", m_pending);
        xml.add_int_element("new_value_pending", m_newValuePending);

    xml.end_element();
}
