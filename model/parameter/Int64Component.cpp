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


void Int64Component::loadState(const QVariantMap& state)
{
    auto value = state.find(QStringLiteral("value"));
    auto min = state.find(QStringLiteral("min"));
    auto max = state.find(QStringLiteral("max"));
    auto pending = state.find(QStringLiteral("pending"));
    auto base = state.find(QStringLiteral("BaseComponent"));

    if (value != state.end())
    {
        m_value = value->value<qint64>();
    }
    if (min != state.end())
    {
        m_min = min->value<qint64>();
    }
    if (max != state.end())
    {
        m_max = max->value<qint64>();
    }
    if (pending != state.end())
    {
        m_newValuePending = true;
        m_pending = pending->value<qint64>();
    }
    if (base != state.end())
    {
        BaseComponent::loadState(base->toMap());
    }
}


QVariantMap Int64Component::storeState() const
{
    QVariantMap state;
    state.insert(QStringLiteral("value"), m_value);
    state.insert(QStringLiteral("min"), m_min);
    state.insert(QStringLiteral("max"), m_max);
    if (m_newValuePending)
    {
        state.insert(QStringLiteral("pending"), m_pending);
    }
    state.insert(QStringLiteral("BaseComponent"), BaseComponent::storeState());
    return state;
}
