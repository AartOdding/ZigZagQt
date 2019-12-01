#include "intparametercomponent.h"
#include "utility/numeric.h"
#include "zigzaglib/xmlserializer.h"

#include <numeric>



IntParameterComponent::IntParameterComponent(int64_t value, BaseParameterOld* parameter)
    : IntParameterComponent(value, std::numeric_limits<int64_t>::lowest(),
                                   std::numeric_limits<int64_t>::max(), parameter)
{

}


IntParameterComponent::IntParameterComponent(int64_t value, int64_t min, int64_t max, BaseParameterOld* parameter)
    : BaseComponent(parameter, BaseComponent::Int64)
{
    min_value = smallest(min, max);
    max_value = largest(min, max);
    current_value = constrain(value, min_value, max_value);
}


bool IntParameterComponent::update()
{
    if (new_value_pending && pending_value != current_value)
    {
        set_value(pending_value);
        new_value_pending = false;
        return true;
    }
    return false;
}


int64_t IntParameterComponent::get() const
{
    return current_value;
}


int64_t IntParameterComponent::get_min() const
{
    return min_value;
}


int64_t IntParameterComponent::get_max() const
{
    return max_value;
}


void IntParameterComponent::set_value(int64_t value)
{
    auto constrained_value = constrain(value, min_value, max_value);
    if (constrained_value != current_value)
    {
        current_value = constrained_value;
        emit valueChanged(current_value);
        emit valueChanged(static_cast<double>(current_value));
    }
}


void IntParameterComponent::set_min(int64_t min)
{
    // min_value shall be no larger than max_value
    auto new_min = smallest(min, max_value);

    if (min_value != new_min)
    {
        min_value = new_min;

        // If min_value increased it could have become higher than current_value.
        set_value(current_value);

        // Emit after value changed is emitted, otherwise we can get a situation where value
        // can be lower than min.
        emit min_changed(min_value);
    }
}


void IntParameterComponent::set_max(int64_t max)
{
    // max_value shall be no smaller than min_value
    auto new_max = largest(max, min_value);

    if (max_value != new_max)
    {
        max_value = new_max;

        // If max_value decreased it could have become lower than current_value.
        set_value(current_value);

        // Emit after value changed is emitted, otherwise we can get a situation where value
        // can be higher than max.
        emit max_changed(max_value);
    }
}


void IntParameterComponent::set(int64_t value)
{
    pending_value = value;
    new_value_pending = pending_value != current_value;
}


void IntParameterComponent::set(double value)
{
    pending_value = value;
    new_value_pending = pending_value != current_value;
}


void IntParameterComponent::readXml(QXmlStreamReader& xml)
{

}


void IntParameterComponent::writeXml(XmlSerializer& xml)
{
    xml.begin_element("IntParameterComponent");

        BaseComponent::writeXml(xml);

        xml.add_int_element("current_value", current_value);
        xml.add_int_element("min_value", min_value);
        xml.add_int_element("max_value", max_value);
        xml.add_int_element("pending_value", pending_value);
        xml.add_int_element("new_value_pending", new_value_pending);

    xml.end_element();
}
