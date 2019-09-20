#include "parametercomponentdouble.h"
#include "utility/numeric.h"

#include <numeric>



ParameterComponentDouble::ParameterComponentDouble(double value, BaseParameter* parameter)
    : ParameterComponentDouble(value, std::numeric_limits<double>::lowest(),
                                      std::numeric_limits<double>::max(), parameter)
{

}


ParameterComponentDouble::ParameterComponentDouble(double value, double min, double max, BaseParameter* parameter)
    : ParameterComponent(parameter, ParameterComponent::Double)
{
    min_value = smallest(min, max);
    max_value = largest(min, max);
    current_value = constrain(value, min_value, max_value);
}


bool ParameterComponentDouble::process_changes()
{
    if (new_value_pending && pending_value != current_value)
    {
        set(pending_value);
        new_value_pending = false;
        return true;
    }
    return false;
}


double ParameterComponentDouble::get() const
{
    return current_value;
}


double ParameterComponentDouble::get_min() const
{
    return min_value;
}


double ParameterComponentDouble::get_max() const
{
    return max_value;
}


bool ParameterComponentDouble::get_update_eager() const
{
    return update_eager;
}


void ParameterComponentDouble::set(double value)
{
    auto constrained_value = constrain(value, min_value, max_value);
    if (constrained_value != current_value)
    {
        current_value = constrained_value;
        emit value_changed(current_value);
        emit value_changed(static_cast<int64_t>(current_value));
    }
}


void ParameterComponentDouble::set_min(double min)
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


void ParameterComponentDouble::set_max(double max)
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


void ParameterComponentDouble::set_later(int64_t value)
{
    pending_value = value;
    new_value_pending = pending_value != current_value;
}


void ParameterComponentDouble::set_later(double value)
{
    pending_value = value;
    new_value_pending = pending_value != current_value;
}


void ParameterComponentDouble::set_update_eager(bool eagerness)
{
    if (update_eager != eagerness)
    {
        update_eager = eagerness;
        emit update_eager_changed(update_eager);
    }
}
