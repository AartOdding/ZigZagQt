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
