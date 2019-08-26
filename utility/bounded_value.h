#pragma once

#include <limits>


template <typename T>
class bounded_value
{
public:

    bounded_value(const T& val = T())
        : bounded_value<T>(val, std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max())
    { }


    bounded_value(const T& val, const T& min, const T& max)
    {
        if (min > max)
        {
            min_value = max;
            max_value = min;
        }
        else
        {
            min_value = min;
            max_value = max;
        }
        if (val < min_value)
        {
            value = min_value;
        }
        else if (val > max_value)
        {
            value = max_value;
        }
        else
        {
            value = val;
        }
    }


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


    void set(T new_value, bool& value_changed)
    {
        if (new_value > max_value)
        {
            new_value = max_value;
        }
        else if (new_value < min_value)
        {
            new_value = min_value;
        }
        value_changed = value != new_value;
        value = new_value;
    }


    void set_min(const T& new_min, bool& value_forced_up)
    {
        if (new_min >= max_value)
        {
            min_value = max_value;
        }
        else
        {
            min_value = new_min;
        }
        if (value < min_value)
        {
            value = min_value;
            value_forced_up = true;
        }
        else
        {
            value_forced_up = false;
        }
    }


    void set_max(const T& new_max, bool& value_forced_down)
    {
        if (new_max <= min_value)
        {
            max_value = min_value;
        }
        else
        {
            max_value = new_max;
        }
        if (value > max_value)
        {
            value = max_value;
            value_forced_down = true;
        }
        else
        {
            value_forced_down = false;
        }
    }


    void set_limits(const T& new_min, const T& new_max, bool& value_forced_to_change)
    {
        if (new_min < new_max)
        {
            min_value = new_max;
            max_value = new_min;
        }
        else
        {
            min_value = new_min;
            max_value = new_max;
        }
        if (value < min_value)
        {
            value = min_value;
            value_forced_to_change = true;
        }
        else if (value > max_value)
        {
            value = max_value;
            value_forced_to_change = true;
        }
        else
        {
            value_forced_to_change = false;
        }
    }


    void set(T new_value)
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


    void operator=(T new_value)
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

