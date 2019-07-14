#include "enumparameter.h"



EnumParameter::EnumParameter(const EnumDefinition& enum_def, ParameterMode mode)
    : BaseParameter("enumeration", mode), enum_definition(&enum_def)
{

}


EnumParameter::EnumParameter(const EnumDefinition& enum_def, int start_value, ParameterMode mode)
    : BaseParameter("enumeration", mode), enum_definition(&enum_def)
{
    if (enum_definition->contains(start_value))
    {
        ordinal = start_value;
    }
}

EnumParameter::EnumParameter(const EnumDefinition& enum_def, const QString& start_value, ParameterMode mode)
    : BaseParameter("enumeration", mode), enum_definition(&enum_def)
{
    if (enum_definition->contains(start_value))
    {
        ordinal = enum_definition->ordinal_of(start_value);
    }
}


void EnumParameter::set(int new_ordinal)
{
    if (enum_definition && enum_definition->contains(new_ordinal))
    {
        ordinal = new_ordinal;
        propagate_changes();
    }
}

void EnumParameter::set(const QString& name)
{
    if (enum_definition && enum_definition->contains(name))
    {
        ordinal = enum_definition->ordinal_of(name);
        propagate_changes();
    }
}

int EnumParameter::get_ordinal() const
{
    return ordinal;
}

QString EnumParameter::get_name() const
{
    return enum_definition->name_of(ordinal);
}

void EnumParameter::operator=(int new_ordinal)
{
    set(new_ordinal);
}

void EnumParameter::operator=(const QString& name)
{
    set(name);
}

