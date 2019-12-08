#include "enumparameter.h"
#include "utility/numeric.h"



EnumPar::EnumPar(BaseZigZagObject * parent, const QString& name, const EnumDefinition& def, int i)
    : BaseParameter(ParameterType::Enum, parent, name),
      definition(&def),
      index(this, i, 0, def.size()-1)
{
}


EnumPar::EnumPar(BaseZigZagObject * parent, const QString& name, const EnumDefinition& def, const QString& value)
    : BaseParameter(ParameterType::Enum, parent, name),
      definition(&def),
      index(this, definition->index_of(value), 0, def.size()-1)
{
}


int EnumPar::get_index() const
{
    return static_cast<int>(index.getValue());
}


const QString& EnumPar::get_text() const
{
    return definition->operator[](static_cast<int>(index.getValue()));
}


const EnumDefinition * EnumPar::get_enum() const
{
    return definition;
}


void EnumPar::set(int new_index)
{
    index.change((int64_t)new_index);
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
