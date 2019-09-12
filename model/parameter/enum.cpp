#include "enum.h"



EnumPar::EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& def, int index)
    : ArithmeticParameter(owner, ParameterType::Enum, name), definition(&def)
{
    if (definition->contains(index))
    {
        current_index = index;
    }
}


EnumPar::EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& def, const char* value)
    : ArithmeticParameter(owner, ParameterType::Enum, name), definition(&def)
{
    auto index = definition->index_of(value);

    if (index != -1)
    {
        current_index = index;
    }
}


void EnumPar::set(int new_index)
{
    if (definition->contains(new_index))
    {
        current_index = new_index;
        flag_changed();
    }
}


void EnumPar::set(const char* new_value)
{
    auto index = definition->index_of(new_value);

    if (index != -1)
    {
        current_index = index;
        flag_changed();
    }
}


EnumPar::operator int() const
{
    return current_index;
}


EnumPar::operator const char *() const
{
    return definition->operator[](current_index).c_str();
}


void EnumPar::operator=(int new_index)
{
    set(new_index);
}


void EnumPar::operator=(const char * new_value)
{
    set(new_value);
}


void EnumPar::import_flagged_changed()
{
    Q_ASSERT(dynamic_cast<ArithmeticParameter*>(get_import()));
    auto i = static_cast<ArithmeticParameter*>(get_import());
    set(i->int_at(0));
}


int32_t EnumPar::int_at(unsigned index) const
{
    return index == 0 ? current_index : 0;
}


double EnumPar::double_at(unsigned index) const
{
    return index == 0 ? current_index : 0;
}

