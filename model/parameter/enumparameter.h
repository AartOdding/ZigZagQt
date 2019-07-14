#pragma once

#include "model/enumdefinition.h"
#include "model/parameter/baseparameter.h"


class EnumParameter : public BaseParameter
{
    Q_OBJECT

public:

    EnumParameter(const EnumDefinition& enum_def, ParameterMode mode = ParameterMode::PASSTHROUGH);

    EnumParameter(const EnumDefinition& enum_def, int start_value, ParameterMode mode = ParameterMode::PASSTHROUGH);

    EnumParameter(const EnumDefinition& enum_def, const QString& start_value, ParameterMode mode = ParameterMode::PASSTHROUGH);

    void set(int ordinal);

    void set(const QString& name);

    int get_ordinal() const;

    QString get_name() const;

    void operator=(int ordinal);

    void operator=(const QString& name);


private:

    int ordinal = INT_MIN;

    const EnumDefinition* enum_definition;


};


