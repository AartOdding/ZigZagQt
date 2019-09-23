#pragma once

#include <vector>
#include <algorithm>
#include <unordered_set>


template<typename T>
typename std::vector<T>::iterator find(std::vector<T>& vec, const T& item)
{
    return std::find(vec.begin(), vec.end(), item);
}


template<typename T>
typename std::vector<T>::const_iterator find(const std::vector<T>& vec, const T& item)
{
    return std::find(vec.cbegin(), vec.cend(), item);
}


template<typename CONTAINER, typename T>
bool contains(const CONTAINER& container, const T& item)
{
    static_assert(std::is_same_v<typename CONTAINER::value_type, T>, "Container needs a data type that is the same as T!");
    return std::find(container.begin(), container.end(), item) != container.end();
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
