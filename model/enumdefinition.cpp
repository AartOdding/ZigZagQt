#include "enumdefinition.h"

#include <QRandomGenerator>



EnumDefinition::EnumDefinition(const QString& name)
    : enum_name(name)
{ }

EnumDefinition::EnumDefinition(const QString& name, std::initializer_list<QString> values)
    : enum_name(name)
{
    int ordinal = 0;
    for (const auto& name : values)
    {
        add(name, ordinal++);
    }
}

EnumDefinition::EnumDefinition(const QString& name, std::initializer_list<std::pair<QString, int>> values)
    : enum_name(name)
{
    for (const auto& v : values)
    {
        add(v.first, v.second);
    }
}

bool EnumDefinition::add(const QString& name)
{
    if (!name_to_ordinal.contains(name))
    {
        for (int attempts = 0; attempts < 100; ++attempts)
        {
            int ordinal = QRandomGenerator::global()->bounded(10 + 10 * size());
            if (!ordinal_to_name.contains(ordinal))
            {
                name_to_ordinal.insert(name, ordinal);
                ordinal_to_name.insert(ordinal, name);
                return true;
            }
        }
    }
    return false;
}

bool EnumDefinition::add(const QString& name, int ordinal)
{
    if (!name_to_ordinal.contains(name) && !ordinal_to_name.contains(ordinal))
    {
        name_to_ordinal.insert(name, ordinal);
        ordinal_to_name.insert(ordinal, name);
        return true;
    }
    return false;
}

bool EnumDefinition::remove(int ordinal)
{
    if (ordinal_to_name.contains(ordinal))
    {
        QString name = ordinal_to_name.value(ordinal);
        name_to_ordinal.remove(name);
        ordinal_to_name.remove(ordinal);
        return true;
    }
    return false;
}

bool EnumDefinition::remove(const QString& name)
{
    if (name_to_ordinal.contains(name))
    {
        int ordinal = name_to_ordinal.value(name);
        name_to_ordinal.remove(name);
        ordinal_to_name.remove(ordinal);
        return true;
    }
    return false;
}

int EnumDefinition::size() const
{
    return ordinal_to_name.size();
}

bool EnumDefinition::contains(int ordinal) const
{
    return ordinal_to_name.contains(ordinal);
}

bool EnumDefinition::contains(const QString& name) const
{
    return name_to_ordinal.contains(name);
}

QString EnumDefinition::name_of(int ordinal) const
{
    if (ordinal_to_name.contains(ordinal))
    {
        return ordinal_to_name.value(ordinal);
    }
    else
    {
        return QString();
    }
}

int EnumDefinition::ordinal_of(const QString& name) const
{
    if (name_to_ordinal.contains(name))
    {
        return name_to_ordinal.value(name);
    }
    else
    {
        return INT_MIN;
    }
}

QHash<int, QString>::ConstIterator EnumDefinition::begin() const
{
    return ordinal_to_name.begin();
}

QHash<int, QString>::ConstIterator EnumDefinition::end() const
{
    return ordinal_to_name.end();
}
