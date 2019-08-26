#pragma once

#include "model/enumdefinition.h"
#include "model/parameter/baseparameter.h"

class ParameterOwner;



namespace parameter
{

    class Enum : public BaseParameter
    {
        Q_OBJECT

    public:

        Enum(ParameterOwner * owner, const EnumDefinition& definition, const char * name, int index = 0);

        Enum(ParameterOwner * owner, const EnumDefinition& definition, const char * name, const char* value);


        void operator=(int index);

        void operator=(const char* current_index);


        operator int() const;

        operator const char *() const;


        const EnumDefinition * const definition;


    public slots:

        void set(int index);

        void set(const char* current_index);


    private:

        int current_index = 0;


    };


}
