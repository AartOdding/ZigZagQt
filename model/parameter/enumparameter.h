#pragma once

#include <QObject>
#include "baseparameter.h"
#include "parametercomponentint64.h"
#include "model/enumdefinition.h"

class ParameterOwner;



class EnumPar : public BaseParameter
{
public:

    EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& definition, int index = 0);
    EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& definition, const char* value);

    int32_t get_index() const;
    const char * get_text() const;

    void set(int index);
    void set(const char* current_index);

    void operator=(int index);
    void operator=(const char* current_index);

    const EnumDefinition * get_enum() const;


    int num_components() const override;

    ParameterComponent* get_component(int index) override;

    const ParameterComponent* get_component(int index) const override;


private:

    const EnumDefinition * definition;

    ParameterComponentInt64 index;

};

