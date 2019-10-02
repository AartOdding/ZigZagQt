#include "enumdefinition.h"

#include <QRandomGenerator>



static std::string null_string;



EnumDefinition::EnumDefinition(const QString& name_)
    : name(name_)
{ }


EnumDefinition::EnumDefinition(const char* name_, std::initializer_list<const char*> values)
    : name(name_)
{
    for (const auto& value : values)
    {
        add_value(value);
    }
}


bool EnumDefinition::add_value(const QString& value)
{
    if (!contains(value))
    {
        enum_values.emplace_back(value);
        return true;
    }
    return false;
}


bool EnumDefinition::insert_value(const QString& value, int index)
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


bool EnumDefinition::remove_value(int index)
{
    if (contains(index))
    {
        enum_values.erase(enum_values.begin() + index);
        emit invalidated_from(index);
        return true;
    }
    return false;
}


bool EnumDefinition::remove_value(const QString& value)
{
    return remove_value(index_of(value));
}


bool EnumDefinition::contains(int index) const
{
    return index >= 0 && index < size();
}


bool EnumDefinition::contains(const QString& value) const
{
    return std::find(enum_values.begin(), enum_values.end(), value) != enum_values.end();
}


int EnumDefinition::index_of(const QString& name) const
{
    auto pos = std::find(enum_values.begin(), enum_values.end(), name);

    if (pos != enum_values.end())
    {
        return static_cast<int>(pos - enum_values.begin());
    }
    else
    {
        return -1;
    }
}


const QString& EnumDefinition::enum_name() const
{
    return name;
}


int EnumDefinition::size() const
{
    return static_cast<int>(enum_values.size());
}


const QString& EnumDefinition::operator[](int index) const
{
    static QString empty_string = "";

    if (contains(index))
    {
        return enum_values[static_cast<std::vector<QString>::size_type>(index)];
    }
    else
    {
        return empty_string;
    }
}


std::vector<QString>::const_iterator EnumDefinition::begin() const
{
    return enum_values.cbegin();
}


std::vector<QString>::const_iterator EnumDefinition::end() const
{
    return enum_values.cend();
}
