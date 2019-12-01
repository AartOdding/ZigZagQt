#include "enumparameter.h"
#include "utility/numeric.h"



EnumPar::EnumPar(BaseParameterOld * parent, const QString& name, const EnumDefinition& def, int i)
    : BaseParameterOld(parent, ParameterType::Enum, name),
      definition(&def),
      index(i, 0, def.size()-1, this)
{
}


EnumPar::EnumPar(BaseParameterOld * parent, const QString& name, const EnumDefinition& def, const QString& value)
    : BaseParameterOld(parent, ParameterType::Enum, name),
      definition(&def),
      index(definition->index_of(value), 0, def.size()-1, this)
{
}


int EnumPar::get_index() const
{
    return static_cast<int>(index.get());
}


const QString& EnumPar::get_text() const
{
    return definition->operator[](static_cast<int>(index.get()));
}


const EnumDefinition * EnumPar::get_enum() const
{
    return definition;
}


void EnumPar::set(int new_index)
{
    index.set((int64_t)new_index);
}


void EnumPar::set(const QString& new_value)
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


void EnumPar::operator=(const QString& new_value)
{
    set(new_value);
}


int EnumPar::num_components() const
{
    return 1;
}


BaseComponent* EnumPar::get_component(int i)
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


const BaseComponent* EnumPar::get_component(int i) const
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
