#pragma once

#include "model/enumdefinition.h"
#include "model/parameter/baseparameter.h"


class EnumParameter : public BaseParameter
{
    Q_OBJECT

public:

    EnumParameter(const EnumDefinition& definition, const char * name,
                  ParameterMode mode = ParameterMode::Passthrough);

    EnumParameter(const EnumDefinition& definition, const char * name,
                  int start_value, ParameterMode mode = ParameterMode::Passthrough);

    EnumParameter(const EnumDefinition& definition, const char * name,
                  const char* current_index, ParameterMode mode = ParameterMode::Passthrough);

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


