#pragma once

#include <QObject>
#include "BaseParameter.hpp"
#include "Int64Component.hpp"
#include "model/enumdefinition.h"



class EnumPar : public BaseParameter
{
public:

    EnumPar(BaseZigZagObject * parent, const QString& name, const EnumDefinition& definition, int index = 0);
    EnumPar(BaseZigZagObject * parent, const QString& name, const EnumDefinition& definition, const QString& value);

    int get_index() const;
    const QString& get_text() const;

    void set(int index);
    void set(const QString& value);

    void operator=(int index);
    void operator=(const QString& value);

    const EnumDefinition * get_enum() const;


private:

    const EnumDefinition * definition;

    Int64Component index;

};

