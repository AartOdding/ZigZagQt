#include "enumparameter.h"



EnumParameter::EnumParameter(const EnumDefinition& def, const char* name, ParameterMode mode)
    : BaseParameter(ParameterType::Enum, name, mode), definition(&def)
{

}


EnumParameter::EnumParameter(const EnumDefinition& def, const char* name, int start_index, ParameterMode mode)
    : BaseParameter(ParameterType::Enum, name, mode), definition(&def)
{
    if (definition->contains(start_index))
    {
        current_index = start_index;
    }
}


EnumParameter::EnumParameter(const EnumDefinition& def, const char* name, const char * start_value, ParameterMode mode)
    : BaseParameter(ParameterType::Enum, name, mode), definition(&def)
{
    auto index = definition->index_of(start_value);

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
        propagate_changes();
    }
}


void EnumParameter::set(const char* new_value)
{
    auto index = definition->index_of(new_value);

    if (index != -1)
    {
        current_index = index;
        propagate_changes();
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

