#include "enumparameter.h"



EnumParameter::EnumParameter(ParameterOwner * owner, const EnumDefinition& def, const char * name, int index)
    : BaseParameter(owner, ParameterType::Enum, name), definition(&def)
{
    if (definition->contains(index))
    {
        current_index = index;
    }
}


EnumParameter::EnumParameter(ParameterOwner * owner, const EnumDefinition& def, const char * name, const char* value)
    : BaseParameter(owner, ParameterType::Enum, name), definition(&def)
{
    auto index = definition->index_of(value);

    if (index != -1)
    {
        current_index = index;
    }
}


void EnumParameter::set(int new_index)
{
    if (definition->contains(new_index))
    {
        current_index = new_index;
        emit_changes();
    }
}


void EnumParameter::set(const char* new_value)
{
    auto index = definition->index_of(new_value);

    if (index != -1)
    {
        current_index = index;
        emit_changes();
    }
}


EnumParameter::operator int() const
{
    return current_index;
}


EnumParameter::operator const char *() const
{
    return definition->operator[](current_index).c_str();
}


void EnumParameter::operator=(int new_index)
{
    set(new_index);
}


void EnumParameter::operator=(const char * new_value)
{
    set(new_value);
}

