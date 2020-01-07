#pragma once

#include <QObject>
#include "BaseParameter.hpp"
#include "Int64Component.hpp"
#include "model/enumdefinition.h"



class EnumParameter : public BaseParameter
{
    Q_OBJECT

public:

    EnumParameter(BaseZigZagObject * parent, const QString& name, const EnumDefinition& m_enum, int m_enumValue = 0);
    EnumParameter(BaseZigZagObject * parent, const QString& name, const EnumDefinition& m_enum, const QString& value);

    int getIndex() const;
    const QString& getText() const;

    void setIndex(int index);
    void setText(const QString& value);

    void operator=(int m_enumValue);
    void operator=(const QString& value);

    const EnumDefinition * getEnum() const;


private:

    const EnumDefinition * m_enum;

    Int64Component m_enumValue;

};

