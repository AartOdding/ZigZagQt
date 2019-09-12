#pragma once

#include "model/enumdefinition.h"
#include "model/parameter/baseparameter.h"

class ParameterOwner;




class EnumPar : public ArithmeticParameter
{
public:

    EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& definition, int index = 0);

    EnumPar(ParameterOwner * owner, const char * name, const EnumDefinition& definition, const char* value);


    void operator=(int index);

    void operator=(const char* current_index);


    operator int() const;

    operator const char *() const;

    void set(int index);

    void set(const char* current_index);


    const EnumDefinition * const definition;

    int32_t int_at(unsigned index) const override;

    double double_at(unsigned index) const override;


protected:

    void import_flagged_changed() override;


private:

    int current_index = 0;


};

