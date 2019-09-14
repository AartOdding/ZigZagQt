#include "enum.h"
#include "utility/constrained.h"



EnumPar::EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& def, int index)
    : ArithmeticParameter(owner, ParameterType::Enum, name), definition(&def)
{
    current_index = constrain(index, 0, definition->size()-1);
}


EnumPar::EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& def, const char* value)
    : ArithmeticParameter(owner, ParameterType::Enum, name), definition(&def)
{
    // Returns -1 if value doesn't exist in enum, constrain will then make it 0 again.
    auto index = definition->index_of(value);
    current_index = constrain(index, 0, definition->size()-1);
}


int32_t EnumPar::get_index() const
{
    return current_index;
}


const char * EnumPar::get_text() const
{
    return definition->text_of(current_index);
}


void EnumPar::set(int new_index)
{
    int temp = constrain(new_index, 0, definition->size()-1);

    if (temp != current_index)
    {
        current_index = temp;
        flag_changed();
    }
}


void EnumPar::set(const char* new_value)
{
    auto index = constrain(definition->index_of(new_value), 0, definition->size()-1);

    if (index != current_index)
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
    return definition->text_of(current_index);
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

