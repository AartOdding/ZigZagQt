#pragma once

#include <vector>
#include <algorithm>


template<typename T>
typename std::vector<T>::iterator find(std::vector<T>& vec, const T& item)
{
    return std::find(vec.begin(), vec.end(), item);
}


template<typename T>
bool contains(std::vector<T>& vec, const T& item)
{
    return find(vec, item) != vec.end();
}


template<typename T>
bool try_erase(std::vector<T>& vec, const T& item)
{
    auto it = find(vec, item);
    if (it != vec.end())
    {
        vec.erase(it);
        return true;
    }
    return false;
}
