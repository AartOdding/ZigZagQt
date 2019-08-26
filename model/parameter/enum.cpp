#include "enum.h"



parameter::Enum::Enum(ParameterOwner * owner, const EnumDefinition& def, const char * name, int index)
    : BaseParameter(owner, ParameterType::Enum, name), definition(&def)
{
    if (definition->contains(index))
    {
        current_index = index;
    }
}


parameter::Enum::Enum(ParameterOwner * owner, const EnumDefinition& def, const char * name, const char* value)
    : BaseParameter(owner, ParameterType::Enum, name), definition(&def)
{
    auto index = definition->index_of(value);

    if (index != -1)
    {
        current_index = index;
    }
}


void parameter::Enum::set(int new_index)
{
    if (definition->contains(new_index))
    {
        current_index = new_index;
        flag_changed();
    }
}


void parameter::Enum::set(const char* new_value)
{
    auto index = definition->index_of(new_value);

    if (index != -1)
    {
        current_index = index;
        flag_changed();
    }
}


parameter::Enum::operator int() const
{
    return current_index;
}


parameter::Enum::operator const char *() const
{
    return definition->operator[](current_index).c_str();
}


void parameter::Enum::operator=(int new_index)
{
    set(new_index);
}


void parameter::Enum::operator=(const char * new_value)
{
    set(new_value);
}

