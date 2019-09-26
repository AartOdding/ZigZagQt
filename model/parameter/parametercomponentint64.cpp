#include "parametercomponentint64.h"
#include "utility/numeric.h"

#include <numeric>



ParameterComponentInt64::ParameterComponentInt64(int64_t value, BaseParameter* parameter)
    : ParameterComponentInt64(value, std::numeric_limits<int64_t>::lowest(),
                                     std::numeric_limits<int64_t>::max(), parameter)
{

}


ParameterComponentInt64::ParameterComponentInt64(int64_t value, int64_t min, int64_t max, BaseParameter* parameter)
    : ParameterComponent(parameter, ParameterComponent::Int64)
{
    min_value = smallest(min, max);
    max_value = largest(min, max);
    current_value = constrain(value, min_value, max_value);
}


bool ParameterComponentInt64::process_changes()
{
    if (new_value_pending && pending_value != current_value)
    {
        set(pending_value);
        new_value_pending = false;
        return true;
    }
    return false;
}


int64_t ParameterComponentInt64::get() const
{
    return current_value;
}


int64_t ParameterComponentInt64::get_min() const
{
    return min_value;
}


int64_t ParameterComponentInt64::get_max() const
{
    return max_value;
}


void ParameterComponentInt64::set(int64_t value)
{
    auto constrained_value = constrain(value, min_value, max_value);
    if (constrained_value != current_value)
    {
        current_value = constrained_value;
        emit value_changed(current_value);
        emit value_changed(static_cast<double>(current_value));
    }
}


void ParameterComponentInt64::set_min(int64_t min)
{
    // min_value shall be no larger than max_value
    auto new_min = smallest(min, max_value);

    if (min_value != new_min)
    {
        min_value = new_min;

        // If min_value increased it could have become higher than current_value.
        set(current_value);

        // Emit after value changed is emitted, otherwise we can get a situation where value
        // can be lower than min.
        emit min_changed(min_value);
    }
}


void ParameterComponentInt64::set_max(int64_t max)
{
    // max_value shall be no smaller than min_value
    auto new_max = largest(max, min_value);

    if (max_value != new_max)
    {
        max_value = new_max;

        // If max_value decreased it could have become lower than current_value.
        set(current_value);

        // Emit after value changed is emitted, otherwise we can get a situation where value
        // can be higher than max.
        emit max_changed(max_value);
    }
}


void ParameterComponentInt64::set_later(int64_t value)
{
    pending_value = value;
    new_value_pending = pending_value != current_value;
}


void ParameterComponentInt64::set_later(double value)
{
    pending_value = value;
    new_value_pending = pending_value != current_value;
}
