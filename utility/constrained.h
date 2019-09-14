#pragma once

#include <limits>


template<typename T>
T constrain(const T& value, const T& min, const T& max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}


template<typename T>
T largest(const T& value1, const T& value2)
{
    if (value1 < value2)
    {
        return value2;
    }
    else
    {
        return value1;
    }
}


template<typename T>
T smallest(const T& value1, const T& value2)
{
    if (value2 < value1)
    {
        return value2;
    }
    else
    {
        return value1;
    }
}


template <typename T>
class constrained
{
public:

    constrained(const T& val = T())
        : constrained<T>(val, std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max())
    { }


    constrained(const T& val, const T& min, const T& max)
    {
        min_value = smallest(min, max);
        max_value = largest(min, max);
        value = constrain(val, min_value, max_value);
    }

    /*
    T constrain(const T& value) const
    {
        return constrain(value, min_value, max_value);
    }*/


    T get() const
    {
        return value;
    }


    T get_min() const
    {
        return  min_value;
    }


    T get_max() const
    {
        return max_value;
    }


    void set(const T& new_value, bool& value_changed)
    {
        auto actual_new_value = constrained(new_value, min_value, max_value);
        value_changed = actual_new_value != value;
        value = actual_new_value;
    }


    void set_min(const T& new_min, bool& value_forced_up)
    {
        min_value = smallest(new_min, max_value);
        auto new_value = largest(value, min_value);
        value_forced_up = new_value != value;
        value = new_value;
    }


    void set_max(const T& new_max, bool& value_forced_down)
    {
        max_value = largest(new_max, min_value);
        auto new_value = smallest(value, max_value);
        value_forced_down = new_value != value;
        value = new_value;
    }


    void set_limits(const T& new_min, const T& new_max, bool& value_forced_to_change)
    {
        min_value = smallest(new_min, new_max);
        max_value = largest(new_min, new_max);
        auto new_value = constrain(value, min_value, max_value);
        value_forced_to_change = new_value != value;
        value = new_value;
    }


    void set(const T& new_value)
    {
        bool placeholder;
        set(new_value, placeholder);
    }


    void set_min(const T& new_min)
    {
        bool placeholder;
        set_min(new_min, placeholder);
    }


    void set_max(const T& new_max)
    {
        bool placeholder;
        set_max(new_max, placeholder);
    }


    void set_limits(const T& new_min, const T& new_max)
    {
        bool placeholder;
        set(new_min, new_max, placeholder);
    }


    void operator=(const T& new_value)
    {
        set(new_value);
    }


    operator T() const
    {
        return value;
    }


private:

    T value;
    T min_value;
    T max_value;

};

