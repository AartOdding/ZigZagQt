#include "enumdefinition.h"

#include <QRandomGenerator>



static std::string null_string;



EnumDefinition::EnumDefinition(const char* n)
    : enum_name(n), name(enum_name.c_str())
{ }


EnumDefinition::EnumDefinition(const char* n, std::initializer_list<const char*> values)
    : enum_name(n), name(enum_name.c_str())
{
    for (const auto& value : values)
    {
        add(value);
    }
}


bool EnumDefinition::add(const char* value)
{
    if (!contains(value))
    {
        enum_values.emplace_back(value);
        return true;
    }
    return false;
}


bool EnumDefinition::insert(const char* value, int index)
{
    if (!contains(value))
    {
        if (index < 0)
        {
            enum_values.emplace(enum_values.begin(), value);
            emit invalidated_from(0);
        }
        else if (index >= size())
        {
            enum_values.emplace_back(value);
        }
        else
        {
            enum_values.emplace(enum_values.begin() + index, value);
            emit invalidated_from(index);
        }
        return true;
    }
    return false;
}


bool EnumDefinition::remove(int index)
{
    if (contains(index))
    {
        enum_values.erase(enum_values.begin() + index);
        emit invalidated_from(index);
        return true;
    }
    return false;
}


bool EnumDefinition::remove(const char* value)
{
    return remove(index_of(value));
}


bool EnumDefinition::contains(int index) const
{
    return index >= 0 && index < size();
}


bool EnumDefinition::contains(const char* value) const
{
    return std::find(enum_values.begin(), enum_values.end(), value) != enum_values.end();
}


int EnumDefinition::index_of(const char* name) const
{
    auto pos = std::find(enum_values.begin(), enum_values.end(), name);

    if (pos != enum_values.end())
    {
        return pos - enum_values.begin();
    }
    else
    {
        return -1;
    }
}


int EnumDefinition::size() const
{
    return enum_values.size();
}


const std::string& EnumDefinition::operator[](int index) const
{
    if (contains(index))
    {
        return enum_values[index];
    }
    else
    {
        return null_string;
    }
}


std::vector<std::string>::const_iterator EnumDefinition::begin() const
{
    return enum_values.cbegin();
}


std::vector<std::string>::const_iterator EnumDefinition::end() const
{
    return enum_values.cend();
}
