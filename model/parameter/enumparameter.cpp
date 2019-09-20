#include "enumparameter.h"
#include "utility/numeric.h"



EnumPar::EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& def, int i)
    : BaseParameter(owner, ParameterType::Enum, name),
      definition(&def),
      index(i, 0, def.size()-1, this)
{
}


EnumPar::EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& def, const char* value)
    : BaseParameter(owner, ParameterType::Enum, name),
      definition(&def),
      index(definition->index_of(value), 0, def.size()-1, this)
{
}


int32_t EnumPar::get_index() const
{
    return index.get();
}


const char * EnumPar::get_text() const
{
    return definition->text_of(index.get());
}


const EnumDefinition * EnumPar::get_enum() const
{
    return definition;
}


void EnumPar::set(int new_index)
{
    index.set(new_index);
}


void EnumPar::set(const char* new_value)
{
    auto index = definition->index_of(new_value);

    if (index != -1)
    {
        set(index);
    }
}


void EnumPar::operator=(int new_index)
{
    set(new_index);
}


void EnumPar::operator=(const char * new_value)
{
    set(new_value);
}


int EnumPar::num_components() const
{
    return 1;
}


ParameterComponent* EnumPar::get_component(int i)
{
    if (i == 0)
    {
        return &index;
    }
    else
    {
        return nullptr;
    }
}


const ParameterComponent* EnumPar::get_component(int i) const
{
    if (i == 0)
    {
        return &index;
    }
    else
    {
        return nullptr;
    }
}
