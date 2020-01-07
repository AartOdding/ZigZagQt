#include "Float64Component.hpp"
#include "utility/numeric.h"

#include <numeric>




Float64Component::Float64Component(BaseParameter* parameter, double value)
    : Float64Component(parameter, value, std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max())
{

}



Float64Component::Float64Component(BaseParameter* parameter, double value, double min, double max)
    : BaseComponent(parameter)
{
    m_min = smallest(min, max);
    m_max = largest(min, max);
    m_value = constrain(value, m_min, m_max);
}



bool Float64Component::update()
{
    if (m_newValuePending)
    {
        return setValue(m_pending, true);
    }
    return false;
}



double Float64Component::getValue() const
{
    return m_value;
}



double Float64Component::getMin() const
{
    return m_min;
}



double Float64Component::getMax() const
{
    return m_max;
}



bool Float64Component::setValue(double value, bool overwritePendingChanges)
{
    if (overwritePendingChanges)
    {
        m_newValuePending = false;
    }

    double constrainedValue = constrain(value, m_min, m_max);

    if (constrainedValue != m_value)
    {
        m_value = constrainedValue;
        emit valueChanged(m_value);
        return true;
    }
    return false;
}



void Float64Component::setMin(double min)
{
    double newMin = smallest(min, m_max); // Min shall not be larger than max.

    if (m_min != newMin)
    {
        m_min = newMin;

        setValue(m_value, false); // Min could have been increased to higher than m_value ...

        // Emit after valueChanged is emitted, otherwise we can get a situation where value
        // can be lower than min.
        emit minChanged(m_min);
    }
}



void Float64Component::setMax(double max)
{
    double newMax = largest(max, m_min); // Max shall not be smaller than min.

    if (m_max != newMax)
    {
        m_max = newMax;

        setValue(m_value, false); // Max could have been decreased to less than m_value ...

        // Emit after valueChanged is emitted, otherwise we can get a situation where value
        // can be higher than max.
        emit maxChanged(m_max);
    }
}



void Float64Component::change(int64_t value)
{
    m_pending = value;
    m_newValuePending = m_pending != m_value;
}



void Float64Component::change(double value)
{
    m_pending = value;
    m_newValuePending = m_pending != m_value;
}


void Float64Component::loadState(const QVariantMap& state)
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


QVariantMap Float64Component::storeState() const
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
