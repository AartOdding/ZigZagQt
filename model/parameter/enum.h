#pragma once

#include "model/enumdefinition.h"
#include "model/parameter/baseparameter.h"

class ParameterOwner;




class EnumPar : BaseParameter
{
public:

    EnumPar(ParameterOwner * owner, const EnumDefinition& definition, const char * name, int index = 0);

    EnumPar(ParameterOwner * owner, const EnumDefinition& definition, const char * name, const char* value);


    void operator=(int index);

    void operator=(const char* current_index);


    operator int() const;

    operator const char *() const;

    void set(int index);

    void set(const char* current_index);


    const EnumDefinition * const definition;



private:

    int current_index = 0;


};

