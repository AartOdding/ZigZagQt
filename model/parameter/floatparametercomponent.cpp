#include "floatparametercomponent.h"
#include "utility/numeric.h"

#include <numeric>



FloatParameterComponent::FloatParameterComponent(double value, BaseParameterOld* parameter)
    : FloatParameterComponent(value, std::numeric_limits<double>::lowest(),
                                      std::numeric_limits<double>::max(), parameter)
{

}


FloatParameterComponent::FloatParameterComponent(double value, double min, double max, BaseParameterOld* parameter)
    : BaseComponent(parameter, BaseComponent::Float64)
{
    min_value = smallest(min, max);
    max_value = largest(min, max);
    current_value = constrain(value, min_value, max_value);
}


bool FloatParameterComponent::update()
{
    if (new_value_pending && pending_value != current_value)
    {
        set_value(pending_value);
        new_value_pending = false;
        return true;
    }
    return false;
}


double FloatParameterComponent::get_value() const
{
    return current_value;
}


double FloatParameterComponent::get_min() const
{
    return min_value;
}


double FloatParameterComponent::get_max() const
{
    return max_value;
}


void FloatParameterComponent::set_value(double value)
{
    auto constrained_value = constrain(value, min_value, max_value);
    if (constrained_value != current_value)
    {
        current_value = constrained_value;
        emit valueChanged(current_value);
        emit valueChanged(static_cast<int64_t>(current_value));
    }
}


void FloatParameterComponent::set_min(double min)
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


void FloatParameterComponent::set_max(double max)
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


void FloatParameterComponent::set(int64_t value)
{
    pending_value = value;
    new_value_pending = pending_value != current_value;
}


void FloatParameterComponent::set(double value)
{
    pending_value = value;
    new_value_pending = pending_value != current_value;
}
